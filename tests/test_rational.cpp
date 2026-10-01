// det J / L^Z with L = x0 + x1 + x2 on P2 tets degenerate at vertex 0
// (classes from generate.py RationalChecks), against the degenerate-state approach.
#include <iostream>
#include <random>
#include "DegenerateHelpers.hpp"
#include "generated/JacEval_P2Tet.hpp"
#include "generated/P2TetValR1.hpp"
#include "generated/P2TetValR2.hpp"
#include "generated/P2TetCGVR2.hpp"
#include <algorithms/solve.hpp>
#include <algorithms/minimize.hpp>

using namespace miso;

template <class C> C val(const Eigen::MatrixXd &cp)
{ return {rv<10>(cp,0,0,tet2_perm), rv<10>(cp,0,1,tet2_perm), rv<10>(cp,0,2,tet2_perm)}; }

template <class C> C cgv(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b)
{ return {rv<10>(a,0,0,tet2_perm), rv<10>(a,0,1,tet2_perm), rv<10>(a,0,2,tet2_perm),
          rv<10>(b,0,0,tet2_perm), rv<10>(b,0,1,tet2_perm), rv<10>(b,0,2,tet2_perm)}; }

using Nodes = double[10][3];

// Reference P2 tet, polyfem node order: vertices, then edges 01, 12, 02, 03, 13, 23.
static const Nodes tet2 = {
    {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {0.5, 0, 0}, {0.5, 0.5, 0}, {0, 0.5, 0},
    {0, 0, 0.5}, {0.5, 0, 0.5}, {0, 0.5, 0.5}
};

// Edges 01 and 02 collapsed onto vertex 0, leading quadratic with a negative
// mixed Bernstein coefficient there (same element as in test_jacobian.cpp).
static const Nodes q2neg = {
    {0.0, 0.0, 0.0},
    {0.6463195691202872, -0.358974358974359, -0.022123893805309734},
    {0.193359375, 0.7662921348314606, 0.07639680729760548},
    {-0.3115727002967359, 0.3189252336448598, 1.2988338192419826},
    {0.0, 0.0, 0.0},
    {0.849083215796897, 0.4112607099143207, -0.33390705679862304},
    {0.0, 0.0, 0.0},
    {0.2540272614622057, -0.046890927624872576, 0.37959667852906287},
    {0.44190871369294604, 0.1673469387755102, 0.682454251883746},
    {-0.0513347022587269, 0.31322751322751324, 0.22068230277185502},
};

static Eigen::MatrixXd mat(const Nodes &c)
{
    Eigen::MatrixXd cp(10, 3);
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 3; ++j)
            cp(i, j) = c[i][j];
    return cp;
}

// Reference tet with the control points of edges 0-w (w in towards) collapsed onto vertex 0.
static Eigen::MatrixXd collapsed(std::initializer_list<int> towards)
{
    Eigen::MatrixXd cp = mat(tet2);
    for (int w : towards) cp.row(w == 1 ? 4 : w == 2 ? 6 : 7) = cp.row(0);
    return cp;
}

int main()
{
    RealInterval::init();
    int passed = 0, failed = 0;
    auto check = [&](const std::string &name, bool ok) {
        std::cout << (ok ? "  PASS: " : "  FAIL: ") << name << "\n";
        ++(ok ? passed : failed);
    };
    Parameters sp;
    sp.constraintEpsilon = {0.0};
    sp.findOne = true;
    sp.maxIter = 20000;

    std::cout << "=== Rational inclusion ===\n";
    {
        // Root inclusion of det J / L^2 contains its value at random points,
        // for random elements with edges 01 and 02 collapsed (order 2).
        std::mt19937 rng(1);
        std::uniform_real_distribution<double> U(0, 1), D(-.3, .3);
        int bad = 0, samples = 0;
        for (int e = 0; e < 200; ++e) {
            Eigen::MatrixXd cp = mat(tet2);
            for (int r : {1, 2, 3, 5, 7, 8, 9})
                for (int j = 0; j < 3; ++j) cp(r, j) += D(rng);
            cp.row(4) = cp.row(6) = cp.row(0);
            const RealInterval inc = val<P2TetValR2>(cp).inclusion(0);
            for (int s = 0; s < 200; ++s) {
                const double a = U(rng), b = U(rng), c = U(rng);
                if (a + b + c > 1 || a + b + c < 1e-3) continue;
                const Real L = Real(a) + Real(b) + Real(c);
                const Real f = JacEval_P2Tet(rv<10>(cp,0,0,tet2_perm), rv<10>(cp,0,1,tet2_perm),
                                             rv<10>(cp,0,2,tet2_perm), Real(a), Real(b), Real(c)) / (L * L);
                ++samples;
                if (upper(f) < lower(inc) || lower(f) > upper(inc)) ++bad;
            }
        }
        check("R2 root inclusion contains det J / L^2 at " + std::to_string(samples) + " random points", bad == 0);
    }

    std::cout << "\n=== Certification ===\n";
    const auto certifies = [&](auto &&dom) {
        Info info{};
        auto sols = solve(std::move(dom), sp, &info);
        return sols.empty() && info.status == Info::Status::completed;
    };
    check("R1, edge 01 collapsed (order 1): valid", certifies(val<P2TetValR1>(collapsed({1}))));
    check("R2, edges 01 and 02 collapsed (order 2): valid", certifies(val<P2TetValR2>(collapsed({1, 2}))));
    {
        const Eigen::MatrixXd a = collapsed({1, 2});
        const Eigen::MatrixXd b = (a.array() + 1.0).matrix();
        Parameters cp;
        cp.targetPrecision = 1e-6;
        cp.constraintEpsilon = {0.0};
        cp.maxIter = 20000;
        check("CGV R2, order-2 element translated: t_lo >= 1", lower(minimize(cgv<P2TetCGVR2>(a, b), cp)) >= 1.0);
    }

    std::cout << "\n=== Comparison (iterations, status: 1 completed, 4 hit maxIter) ===\n";
    Parameters all = sp;
    all.findOne = false;
    const auto report = [&](const char *name, auto &&dom) {
        Info info{};
        auto sols = solve(std::move(dom), all, &info);
        std::cout << "  " << name << ": solutions=" << sols.size() << " status=" << int(info.status)
                  << " iterations=" << info.numIterations << " depth=" << info.reachedDepth << "\n";
    };
    report("order 1, rational R1            ", val<P2TetValR1>(collapsed({1})));
    report("order 1, degenerate state       ", make_p2tet_val_degenerate(collapsed({1}), 0, 0, {1}));
    report("order 2, rational R2            ", val<P2TetValR2>(collapsed({1, 2})));
    report("order 2, degenerate state       ", make_p2tet_val_degenerate(collapsed({1, 2}), 0, 0, {1, 2}));
    report("order 2, rational R1 (Z too low)", val<P2TetValR1>(collapsed({1, 2})));
    report("q2neg, rational R2              ", val<P2TetValR2>(mat(q2neg)));
    report("q2neg, degenerate state         ", make_p2tet_val_degenerate(mat(q2neg), 0, 0, {1, 2}));

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    RealInterval::deinit();
    return failed > 0 ? 1 : 0;
}
