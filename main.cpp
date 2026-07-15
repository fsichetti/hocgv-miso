#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "generated/P3TetVal.hpp"
#include "generated/P3TetCGV.hpp"
#include "algorithms/solve.hpp"
#include "algorithms/minimize.hpp"

using namespace miso;

static constexpr std::size_t element_size = 60;

static std::vector<double> read_binary(const std::string &path, std::size_t element_id) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << path << std::endl;
        std::exit(1);
    }

    file.seekg(0, std::ios::end);
    const auto file_size = file.tellg();
    const auto element_bytes = static_cast<std::streamoff>(element_size * sizeof(double));
    if (file_size < 0 || file_size % element_bytes != 0) {
        std::cerr << "File size is not a multiple of " << element_size
                  << " doubles: " << path << std::endl;
        std::exit(1);
    }

    const auto element_count = static_cast<std::size_t>(file_size / element_bytes);
    if (element_id >= element_count) {
        std::cerr << "element_id " << element_id << " is out of range for " << path
                  << " (contains " << element_count << " elements)" << std::endl;
        std::exit(1);
    }

    file.seekg(static_cast<std::streamoff>(element_id) * element_bytes, std::ios::beg);
    std::vector<double> data(element_size);
    if (!file.read(reinterpret_cast<char *>(data.data()), element_bytes)) {
        std::cerr << "Failed to read element " << element_id << " from " << path << std::endl;
        std::exit(1);
    }
    return data;
}

// Input data is interleaved in polyfem's P3 tet node ordering:
//   x0,y0,z0, x1,y1,z1, ..., x19,y19,z19
// tet3_perm maps miso slot i -> polyfem node index, matching EigenAdapters.hpp.
static constexpr int tet3_perm[20] = {0, 10, 11, 3, 9, 19, 15, 8, 14, 2, 4, 17, 13, 16, 18, 7, 5, 12, 6, 1};

// col: 0=x, 1=y, 2=z
template <int N>
static RealVector<N> to_rv(const std::vector<double> &data, int col) {
    RealVector<N> v;
    for (int i = 0; i < N; ++i)
        v[i] = data[tet3_perm[i] * 3 + col];
    return v;
}

static void run_val(const std::vector<double> &data) {
    if (data.size() != 60) {
        std::cerr << "Expected 60 doubles (20 nodes * 3 coords), got " << data.size() << std::endl;
        std::exit(1);
    }

    auto px = to_rv<20>(data, 0);
    auto py = to_rv<20>(data, 1);
    auto pz = to_rv<20>(data, 2);

    P3TetVal domain(px, py, pz);

    Info info;
    auto sols = solve(std::move(domain), {0.0}, 1'000'000, true, 0., &info);

    std::cout << "=== P3TetVal (Static Validity) ===" << std::endl;
    std::cout << "Status: " << info.description() << std::endl;
    std::cout << "Success: " << (info.success() ? "yes" : "no") << std::endl;
    std::cout << "Reached depth: " << info.reachedDepth << std::endl;
    std::cout << "Iterations: " << info.numIterations << std::endl;
    std::cout << "Valid: " << (sols.empty() ? "yes" : "no") << std::endl;
    std::cout << "Violation subdomains: " << sols.size() << std::endl;

    for (size_t i = 0; i < sols.size(); ++i) {
        std::cout << "  Subdomain " << i << ": " << sols[i] << std::endl;
    }
}

static void run_cgv(const std::vector<double> &data0, const std::vector<double> &data1) {
    if (data0.size() != 60) {
        std::cerr << "File 1: expected 60 doubles, got " << data0.size() << std::endl;
        std::exit(1);
    }
    if (data1.size() != 60) {
        std::cerr << "File 2: expected 60 doubles, got " << data1.size() << std::endl;
        std::exit(1);
    }

    auto p0x = to_rv<20>(data0, 0);
    auto p0y = to_rv<20>(data0, 1);
    auto p0z = to_rv<20>(data0, 2);
    auto p1x = to_rv<20>(data1, 0);
    auto p1y = to_rv<20>(data1, 1);
    auto p1z = to_rv<20>(data1, 2);

    P3TetCGV domain(p0x, p0y, p0z, p1x, p1y, p1z);

    Info info;
    auto result = minimize(std::move(domain), 1e-2, {0.0}, 1e4, 0, 0., &info);

    std::cout << "=== P3TetCGV (Continuous Geometric Validity) ===" << std::endl;
    std::cout << "Status: " << info.description() << std::endl;
    std::cout << "Success: " << (info.success() ? "yes" : "no") << std::endl;
    std::cout << "Reached depth: " << info.reachedDepth << std::endl;
    std::cout << "Iterations: " << info.numIterations << std::endl;
    std::cout << "Result interval: [" << lower(result) << ", " << upper(result) << "]" << std::endl;
    std::cout << "Fully valid (t >= 1): " << (lower(result) >= 1.0 ? "yes" : "no") << std::endl;
}

static void run_val_interp(const std::vector<double> &data0, const std::vector<double> &data1, double t) {
    if (data0.size() != 60) {
        std::cerr << "File 1: expected 60 doubles, got " << data0.size() << std::endl;
        std::exit(1);
    }
    if (data1.size() != 60) {
        std::cerr << "File 2: expected 60 doubles, got " << data1.size() << std::endl;
        std::exit(1);
    }

    Real rt(t), one_minus_rt(1.0 - t);

    auto interp = [&](int col) {
        return one_minus_rt * to_rv<20>(data0, col) + rt * to_rv<20>(data1, col);
    };

    P3TetVal domain(interp(0), interp(1), interp(2));

    Info info;
    auto sols = solve(std::move(domain), {0.0}, 1'000'000, true, 0., &info);

    std::cout << "=== P3TetVal (Static Validity at t=" << t << ") ===" << std::endl;
    std::cout << "Status: " << info.description() << std::endl;
    std::cout << "Success: " << (info.success() ? "yes" : "no") << std::endl;
    std::cout << "Reached depth: " << info.reachedDepth << std::endl;
    std::cout << "Iterations: " << info.numIterations << std::endl;
    std::cout << "Valid: " << (sols.empty() ? "yes" : "no") << std::endl;
    std::cout << "Violation subdomains: " << sols.size() << std::endl;

    for (size_t i = 0; i < sols.size(); ++i) {
        std::cout << "  Subdomain " << i << ": " << sols[i] << std::endl;
    }
}

int main(int argc, char **argv) {
	Real::init();
    std::size_t element_id = 0;
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--element-id") {
            if (++i >= argc) {
                std::cerr << "Missing value after --element-id" << std::endl;
                return 1;
            }
            try {
                std::size_t parsed = 0;
                const std::string value = argv[i];
                element_id = std::stoull(value, &parsed);
                if (parsed != value.size() || (!value.empty() && value.front() == '-'))
                    throw std::invalid_argument("invalid element_id");
            } catch (const std::exception &) {
                std::cerr << "Invalid element_id: " << argv[i] << std::endl;
                return 1;
            }
        } else {
            args.push_back(arg);
        }
    }

    if (args.empty() || args.size() > 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <file1.bin> [file2.bin [t]] [--element-id N]" << std::endl;
        std::cerr << "  One file:        static validity check (P3TetVal)" << std::endl;
        std::cerr << "  Two files:       continuous geometric validity (P3TetCGV)" << std::endl;
        std::cerr << "  Two files + t:   static validity at interpolated config (P3TetVal)" << std::endl;
        std::cerr << "  --element-id N:  read zero-based element N (60 doubles per element; default 0)" << std::endl;
        return 1;
    }

    if (args.size() == 1) {
        auto data = read_binary(args[0], element_id);
        run_val(data);
    } else if (args.size() == 2) {
        auto data0 = read_binary(args[0], element_id);
        auto data1 = read_binary(args[1], element_id);
        run_cgv(data0, data1);
    } else {
        double t = std::stod(args[2]);
        auto data0 = read_binary(args[0], element_id);
        auto data1 = read_binary(args[1], element_id);
        run_val_interp(data0, data1, t);
    }

	Real::deinit();
    return 0;
}
