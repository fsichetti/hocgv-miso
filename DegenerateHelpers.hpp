#pragma once
#include "EigenAdapters.hpp"

// Degenerate element builders, in polyfem's own vertex numbering and node
// order.
//
// P2TetVal/P3TetVal/P2TetCGV/P3TetCGV were generated with allow_degenerate=2:
// det J can be certified positive everywhere except a chosen tet vertex,
// where it is allowed to vanish (to first or second order) because enough of
// the incident edge control points collapse onto that vertex's own control
// point. The plain make_pXtet_*() factories in EigenAdapters.hpp build the
// class from a polyfem-ordered control point matrix but know nothing about
// which vertex is degenerate; degenerateStateFromVertices(), meanwhile,
// expects a bitmask over miso's own Domain.vertices order, and collapsing a
// control point has to target the right polyfem row *before* that gets
// permuted into miso's lattice. These wrappers do all three steps from
// purely polyfem-side inputs:
//   - vertex: polyfem-local vertex index (0..3) where det J is allowed to vanish
//   - collapseTowards: 1 or 2 of the *other* polyfem vertex indices, selecting
//     which incident edges' near control points collapse onto `vertex` (their
//     count is also the certified vanishing order)
// so a caller who already thinks in polyfem's element/node convention never
// has to touch miso's internal ordering.

namespace miso {

namespace detail {

	// polyfem-local vertex index -> miso Domain.vertices index. Both list the
	// same 4 reference-tet corners, just in different fixed orders: polyfem's
	// p_nodes_3d gives v0=(0,0,0), v1=(1,0,0), v2=(0,1,0), v3=(0,0,1); miso's
	// Domain.vertices (X's factor of X*T, X=(x0,x1,x2)) is
	// [(0,0,0),(0,0,1),(0,1,0),(1,0,0)].
	inline constexpr unsigned tetPolyfemVertexToDomain[4] = {0, 3, 2, 1};

	// polyfem row of the control point nearest polyfem vertex `v` (row) on the
	// edge to polyfem vertex `w` (column), from polyfem's p_nodes_3d layout
	// (see tet2/tet3 in tests/test_jacobian.cpp). Quadratic tets have a single,
	// shared control point per edge; cubic tets have two, one near each end.
	inline constexpr int tet2NearEdgeCP[4][4] = {
		{-1, 4, 6, 7},
		{4, -1, 5, 8},
		{6, 5, -1, 9},
		{7, 8, 9, -1},
	};
	inline constexpr int tet3NearEdgeCP[4][4] = {
		{-1, 4, 9, 10},
		{5, -1, 6, 12},
		{8, 7, -1, 14},
		{11, 13, 15, -1},
	};

} // namespace detail

inline P2TetVal make_p2tet_val_degenerate(const Eigen::MatrixXd &cp, int offset, int vertex,
                                           std::initializer_list<int> collapseTowards)
{
	auto dom = make_p2tet_val(cp, offset);
	dom.degenerateState = P2TetVal::degenerateStateFromVertices(
		1u << detail::tetPolyfemVertexToDomain[vertex],
		static_cast<unsigned>(collapseTowards.size()));
	return dom;
}

inline P3TetVal make_p3tet_val_degenerate(const Eigen::MatrixXd &cp, int offset, int vertex,
                                           std::initializer_list<int> collapseTowards)
{
	auto dom = make_p3tet_val(cp, offset);
	dom.degenerateState = P3TetVal::degenerateStateFromVertices(
		1u << detail::tetPolyfemVertexToDomain[vertex],
		static_cast<unsigned>(collapseTowards.size()));
	return dom;
}

// CGV: the collapse is applied identically to both endpoints of the
// space-time blend (cp1 at t=0, cp2 at t=1), so it holds at every t -- the
// vertex becomes an edge in time. domain.vertices for X*T enumerates
// (spatial vertex, t) with t varying fastest, so spatial vertex m is product
// vertices 2*m (t=0) and 2*m+1 (t=1); the degenerate face is their union.

inline P2TetCGV make_p2tet_cgv_degenerate(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2,
                                           int offset, int vertex,
                                           std::initializer_list<int> collapseTowards)
{
	auto dom = make_p2tet_cgv(cp1, cp2, offset);
	const unsigned m = detail::tetPolyfemVertexToDomain[vertex];
	dom.degenerateState = P2TetCGV::degenerateStateFromVertices(
		(1u << (2 * m)) | (1u << (2 * m + 1)),
		static_cast<unsigned>(collapseTowards.size()));
	return dom;
}

inline P3TetCGV make_p3tet_cgv_degenerate(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2,
                                           int offset, int vertex,
                                           std::initializer_list<int> collapseTowards)
{
	auto dom = make_p3tet_cgv(cp1, cp2, offset);
	const unsigned m = detail::tetPolyfemVertexToDomain[vertex];
	dom.degenerateState = P3TetCGV::degenerateStateFromVertices(
		(1u << (2 * m)) | (1u << (2 * m + 1)),
		static_cast<unsigned>(collapseTowards.size()));
	return dom;
}

} // namespace miso
