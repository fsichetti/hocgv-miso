// Example: using the degenerate-inclusion machinery on a cubic tetrahedron.
//
// P3TetVal represents det J of a cubic (P3) tet map as a Bernstein
// polynomial over the reference tet. If two of the three Bezier control
// points on the edges meeting at a corner are collapsed onto that corner's
// own control point, det J is known -- by construction -- to vanish there to
// second order. Left as a plain RealVector::inclusion() min/max, that zero
// coefficient (and the ring of neighboring coefficients it also forces to
// zero) pins every subdomain touching the corner at lower <= 0 forever, and
// solve() never terminates with a clean answer.
//
// generate.py generated P3TetVal with allow_degenerate=2, so the class knows,
// for every vertex and orders 1 and 2, which Bernstein coefficients are
// allowed to be (and are assert-checked to be) exactly zero there, and
// excludes them from the inclusion bound instead. make_p3tet_val_degenerate()
// (DegenerateHelpers.hpp) builds such an element from purely polyfem-side
// inputs -- a polyfem-ordered control point matrix, the polyfem vertex index
// where det J vanishes, and which other vertices' incident edges collapse
// onto it -- so the caller never has to reason about miso's own lattice
// ordering.
//
// This walks all 12 "two edges collapsed at one corner" configurations of a
// cubic tet: 4 vertices, each with 3 incident edges, C(3,2) = 3 ways to pick
// 2 of them to collapse -- 4*3 = 12 cases. Every one still certifies as
// valid (empty solution set), since the map is the identity everywhere else.

#include <iostream>
#include "DegenerateHelpers.hpp"
#include <algorithms/solve.hpp>

using namespace miso;

// Reference cubic tet nodes, in polyfem's p_nodes_3d order (see tet3 in
// tests/test_jacobian.cpp for the fully commented version).
static const double tet3[20][3] = {
    {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {1./3, 0, 0}, {2./3, 0, 0},
    {2./3, 1./3, 0}, {1./3, 2./3, 0},
    {0, 2./3, 0}, {0, 1./3, 0},
    {0, 0, 1./3}, {0, 0, 2./3},
    {2./3, 0, 1./3}, {1./3, 0, 2./3},
    {0, 2./3, 1./3}, {0, 1./3, 2./3},
    {1./3, 1./3, 0}, {1./3, 0, 1./3},
    {1./3, 1./3, 1./3}, {0, 1./3, 1./3}
};

int main()
{
    Eigen::MatrixXd cp(20, 3);
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 3; ++j)
            cp(i, j) = tet3[i][j];

    Parameters solve_params;
    solve_params.constraintEpsilon = {0.0};
    solve_params.findOne = true;

    // Each vertex's 3 incident edges (its 3 fellow vertices), and the 3 ways
    // to pick 2 of them to collapse.
    static const int others[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
    static const int pairs[3][2] = {{0, 1}, {0, 2}, {1, 2}};

    int passed = 0, failed = 0;
    for (int v = 0; v < 4; ++v) {
        for (const auto &pr : pairs) {
            const int w0 = others[v][pr[0]], w1 = others[v][pr[1]];
            auto dom = make_p3tet_val_degenerate(cp, 0, v, {w0, w1});
            auto sols = solve(std::move(dom), solve_params);

            const bool ok = sols.empty();
            std::cout << "  vertex " << v << ", edges to {" << w0 << "," << w1
                       << "} collapsed: " << (ok ? "PASS" : "FAIL") << "\n";
            ok ? ++passed : ++failed;
        }
    }

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed > 0 ? 1 : 0;
}
