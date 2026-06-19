#pragma once
#include <Eigen/Core>

#include "generated/P1TriCGV.hpp"
#include "generated/P2TriVal.hpp"
#include "generated/P2TriCGV.hpp"
#include "generated/P3TriVal.hpp"
#include "generated/P3TriCGV.hpp"
#include "generated/P4TriVal.hpp"
#include "generated/P4TriCGV.hpp"
#include "generated/P1TetCGV.hpp"
#include "generated/P2TetVal.hpp"
#include "generated/P2TetCGV.hpp"
#include "generated/P3TetVal.hpp"
#include "generated/P3TetCGV.hpp"

#include "generated/JacEval_P1Tri.hpp"
#include "generated/JacEval_P2Tri.hpp"
#include "generated/JacEval_P3Tri.hpp"
#include "generated/JacEval_P4Tri.hpp"
#include "generated/JacEval_P1Tet.hpp"
#include "generated/JacEval_P2Tet.hpp"
#include "generated/JacEval_P3Tet.hpp"

namespace miso {

// Extract N rows from column `col` of `m` starting at `offset`,
// applying an optional index permutation (used for lexicographic reordering).
template<int N>
inline RealVector<N> rv(const Eigen::MatrixXd &m, int offset, int col, const int *perm = nullptr)
{
	RealVector<N> v;
	for (int i = 0; i < N; ++i)
		v[i] = m(offset + (perm ? perm[i] : i), col);
	return v;
}

// Lexicographic permutations for classes with >= 10 nodes.
// miso names parameters px0, px1, px10, ..., px19, px2, ... so index 10 sorts before 2.
static constexpr int perm15[] = {0, 1, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9};
static constexpr int perm20[] = {0, 1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 3, 4, 5, 6, 7, 8, 9};

// ---- Val (static validity) factories ----

inline P2TriVal make_p2tri_val(const Eigen::MatrixXd &cp, int o)
{ return {rv<6>(cp,o,0), rv<6>(cp,o,1)}; }

inline P3TriVal make_p3tri_val(const Eigen::MatrixXd &cp, int o)
{ return {rv<10>(cp,o,0), rv<10>(cp,o,1)}; }

inline P4TriVal make_p4tri_val(const Eigen::MatrixXd &cp, int o)
{ return {rv<15>(cp,o,0,perm15), rv<15>(cp,o,1,perm15)}; }

inline P2TetVal make_p2tet_val(const Eigen::MatrixXd &cp, int o)
{ return {rv<10>(cp,o,0), rv<10>(cp,o,1), rv<10>(cp,o,2)}; }

inline P3TetVal make_p3tet_val(const Eigen::MatrixXd &cp, int o)
{ return {rv<20>(cp,o,0,perm20), rv<20>(cp,o,1,perm20), rv<20>(cp,o,2,perm20)}; }

// ---- CGV (continuous geometric validity) factories ----

inline P1TriCGV make_p1tri_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<3>(cp1,o,0), rv<3>(cp1,o,1), rv<3>(cp2,o,0), rv<3>(cp2,o,1)}; }

inline P2TriCGV make_p2tri_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<6>(cp1,o,0), rv<6>(cp1,o,1), rv<6>(cp2,o,0), rv<6>(cp2,o,1)}; }

inline P3TriCGV make_p3tri_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<10>(cp1,o,0), rv<10>(cp1,o,1), rv<10>(cp2,o,0), rv<10>(cp2,o,1)}; }

inline P4TriCGV make_p4tri_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<15>(cp1,o,0,perm15), rv<15>(cp1,o,1,perm15), rv<15>(cp2,o,0,perm15), rv<15>(cp2,o,1,perm15)}; }

inline P1TetCGV make_p1tet_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<4>(cp1,o,0), rv<4>(cp1,o,1), rv<4>(cp1,o,2), rv<4>(cp2,o,0), rv<4>(cp2,o,1), rv<4>(cp2,o,2)}; }

inline P2TetCGV make_p2tet_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<10>(cp1,o,0), rv<10>(cp1,o,1), rv<10>(cp1,o,2), rv<10>(cp2,o,0), rv<10>(cp2,o,1), rv<10>(cp2,o,2)}; }

inline P3TetCGV make_p3tet_cgv(const Eigen::MatrixXd &cp1, const Eigen::MatrixXd &cp2, int o)
{ return {rv<20>(cp1,o,0,perm20), rv<20>(cp1,o,1,perm20), rv<20>(cp1,o,2,perm20),
          rv<20>(cp2,o,0,perm20), rv<20>(cp2,o,1,perm20), rv<20>(cp2,o,2,perm20)}; }

} // namespace miso
