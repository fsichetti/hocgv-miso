#include "../P3TetVal.hpp"
#include <stdexcept>
namespace miso {
	namespace {
		constexpr std::array<unsigned, 29> kDegenerateStateVertices = {0u, 8u, 8u, 4u, 4u, 2u, 2u, 1u, 1u, 12u, 12u, 10u, 10u, 9u, 9u, 6u, 6u, 5u, 5u, 3u, 3u, 14u, 14u, 13u, 13u, 11u, 11u, 7u, 7u};
		constexpr std::array<unsigned, 29> kDegenerateStateOrders = {0u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u};
		constexpr std::array<std::array<unsigned, 8>, 29> kDegenerateTransitions = {{
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 0, 0, 0, 0, 0, 0},
			{0, 2, 0, 0, 0, 0, 0, 0},
			{0, 0, 3, 0, 0, 0, 0, 0},
			{0, 0, 4, 0, 0, 0, 0, 0},
			{0, 0, 0, 5, 0, 0, 0, 0},
			{0, 0, 0, 6, 0, 0, 0, 0},
			{7, 0, 0, 0, 0, 0, 0, 0},
			{8, 0, 0, 0, 0, 0, 0, 0},
			{0, 9, 9, 0, 0, 3, 0, 1},
			{0, 10, 10, 0, 0, 4, 0, 2},
			{0, 11, 0, 11, 5, 5, 3, 3},
			{0, 12, 0, 12, 6, 6, 4, 4},
			{13, 13, 0, 0, 7, 7, 0, 0},
			{14, 14, 0, 0, 8, 8, 0, 0},
			{0, 0, 15, 15, 0, 0, 5, 5},
			{0, 0, 16, 16, 0, 0, 6, 6},
			{17, 0, 17, 0, 1, 1, 7, 7},
			{18, 0, 18, 0, 2, 2, 8, 8},
			{19, 0, 0, 19, 3, 0, 1, 0},
			{20, 0, 0, 20, 4, 0, 2, 0},
			{0, 21, 21, 21, 5, 15, 15, 21},
			{0, 22, 22, 22, 6, 16, 16, 22},
			{23, 23, 23, 0, 13, 23, 7, 13},
			{24, 24, 24, 0, 14, 24, 8, 14},
			{25, 25, 0, 25, 27, 19, 9, 3},
			{26, 26, 0, 26, 28, 20, 10, 4},
			{27, 0, 27, 27, 9, 1, 25, 19},
			{28, 0, 28, 28, 10, 2, 26, 20},
		}};
	}

	unsigned P3TetVal::degenerateStateFromVertices(unsigned vertexMask, unsigned order) {
		if (vertexMask == 0u) return 0u;
		for (unsigned s=0; s<29; ++s) {
			if (kDegenerateStateVertices[s] == vertexMask && kDegenerateStateOrders[s] == order) return s;
		}
		throw std::invalid_argument("No degenerate state for this vertex set and order");
	}
	unsigned P3TetVal::degenerateStateVertexMask(unsigned s) { return kDegenerateStateVertices[s]; }
	unsigned P3TetVal::degenerateStateOrder(unsigned s) { return kDegenerateStateOrders[s]; }
	unsigned P3TetVal::degenerateTransition(unsigned s, unsigned q) { return kDegenerateTransitions[s][q]; }

	P3TetVal::P3TetVal(const P3TetVal &parent, unsigned q,
		const RealVector<84> &m0,
		const RealVector<4> &x0,
		const RealVector<4> &x1,
		const RealVector<4> &x2
	) :
	m0(m0),
	x0(x0),
	x1(x1),
	x2(x2)
	{ inherit(parent, q); }

	P3TetVal::P3TetVal(
		const RealVector<20> &px,
		const RealVector<20> &py,
		const RealVector<20> &pz
	) :
	m0(LB_3p6(CL_m0(px, py, pz))),
	x0{0, 0, 0, 1},
	x1{0, 0, 1, 0},
	x2{0, 1, 0, 0}
	{
		history = std::make_shared<SubdivHistory>();
	}

	void P3TetVal::inherit(const P3TetVal &parent, unsigned q) {
		depth = parent.depth + 1;
		history = std::make_shared<SubdivHistory>(q, parent.history);
		degenerateState = kDegenerateTransitions[parent.degenerateState][q];
	}
	RealInterval P3TetVal::inclusion(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return m0.inclusionDegenerate<83>();
				case 2: return m0.inclusionDegenerate<80,81,82,83>();
				case 3: return m0.inclusionDegenerate<27>();
				case 4: return m0.inclusionDegenerate<25,26,27,48>();
				case 5: return m0.inclusionDegenerate<6>();
				case 6: return m0.inclusionDegenerate<5,6,12,33>();
				case 7: return m0.inclusionDegenerate<0>();
				case 8: return m0.inclusionDegenerate<0,1,7,28>();
				case 9: return m0.inclusionDegenerate<27,48,63,73,79,82,83>();
				case 10: return m0.inclusionDegenerate<25,26,27,46,47,48,61,62,63,71,72,73,77,78,79,80,81,82,83>();
				case 11: return m0.inclusionDegenerate<6,33,53,67,76,81,83>();
				case 12: return m0.inclusionDegenerate<5,6,12,32,33,38,52,53,57,66,67,70,75,76,78,80,81,82,83>();
				case 13: return m0.inclusionDegenerate<0,28,49,64,74,80,83>();
				case 14: return m0.inclusionDegenerate<0,1,7,28,29,34,49,50,54,64,65,68,74,75,77,80,81,82,83>();
				case 15: return m0.inclusionDegenerate<6,12,17,21,24,26,27>();
				case 16: return m0.inclusionDegenerate<5,6,11,12,16,17,20,21,23,24,25,26,27,33,38,42,45,47,48>();
				case 17: return m0.inclusionDegenerate<0,7,13,18,22,25,27>();
				case 18: return m0.inclusionDegenerate<0,1,7,8,13,14,18,19,22,23,25,26,27,28,34,39,43,46,48>();
				case 19: return m0.inclusionDegenerate<0,1,2,3,4,5,6>();
				case 20: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,28,29,30,31,32,33>();
				case 21: return m0.inclusionDegenerate<6,12,17,21,24,26,27,33,38,42,45,47,48,53,57,60,62,63,67,70,72,73,76,78,79,81,82,83>();
				case 22: return m0.inclusionDegenerate<5,6,11,12,16,17,20,21,23,24,25,26,27,32,33,37,38,41,42,44,45,46,47,48,52,53,56,57,59,60,61,62,63,66,67,69,70,71,72,73,75,76,77,78,79,80,81,82,83>();
				case 23: return m0.inclusionDegenerate<0,7,13,18,22,25,27,28,34,39,43,46,48,49,54,58,61,63,64,68,71,73,74,77,79,80,82,83>();
				case 24: return m0.inclusionDegenerate<0,1,7,8,13,14,18,19,22,23,25,26,27,28,29,34,35,39,40,43,44,46,47,48,49,50,54,55,58,59,61,62,63,64,65,68,69,71,72,73,74,75,77,78,79,80,81,82,83>();
				case 25: return m0.inclusionDegenerate<0,1,2,3,4,5,6,28,29,30,31,32,33,49,50,51,52,53,64,65,66,67,74,75,76,80,81,83>();
				case 26: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,28,29,30,31,32,33,34,35,36,37,38,49,50,51,52,53,54,55,56,57,64,65,66,67,68,69,70,74,75,76,77,78,80,81,82,83>();
				case 27: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27>();
				case 28: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48>();
				default: return m0.inclusion();
			}
			default: throw std::logic_error("Undefined inclusion function");
		}
	}
	RealVector<P3TetVal::numVertices> P3TetVal::sample(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return maskDegenerate<3>(m0.sample<0,6,27,83>());
				case 2: return maskDegenerate<3>(m0.sample<0,6,27,83>());
				case 3: return maskDegenerate<2>(m0.sample<0,6,27,83>());
				case 4: return maskDegenerate<2>(m0.sample<0,6,27,83>());
				case 5: return maskDegenerate<1>(m0.sample<0,6,27,83>());
				case 6: return maskDegenerate<1>(m0.sample<0,6,27,83>());
				case 7: return maskDegenerate<0>(m0.sample<0,6,27,83>());
				case 8: return maskDegenerate<0>(m0.sample<0,6,27,83>());
				case 9: return maskDegenerate<2,3>(m0.sample<0,6,27,83>());
				case 10: return maskDegenerate<2,3>(m0.sample<0,6,27,83>());
				case 11: return maskDegenerate<1,3>(m0.sample<0,6,27,83>());
				case 12: return maskDegenerate<1,3>(m0.sample<0,6,27,83>());
				case 13: return maskDegenerate<0,3>(m0.sample<0,6,27,83>());
				case 14: return maskDegenerate<0,3>(m0.sample<0,6,27,83>());
				case 15: return maskDegenerate<1,2>(m0.sample<0,6,27,83>());
				case 16: return maskDegenerate<1,2>(m0.sample<0,6,27,83>());
				case 17: return maskDegenerate<0,2>(m0.sample<0,6,27,83>());
				case 18: return maskDegenerate<0,2>(m0.sample<0,6,27,83>());
				case 19: return maskDegenerate<0,1>(m0.sample<0,6,27,83>());
				case 20: return maskDegenerate<0,1>(m0.sample<0,6,27,83>());
				case 21: return maskDegenerate<1,2,3>(m0.sample<0,6,27,83>());
				case 22: return maskDegenerate<1,2,3>(m0.sample<0,6,27,83>());
				case 23: return maskDegenerate<0,2,3>(m0.sample<0,6,27,83>());
				case 24: return maskDegenerate<0,2,3>(m0.sample<0,6,27,83>());
				case 25: return maskDegenerate<0,1,3>(m0.sample<0,6,27,83>());
				case 26: return maskDegenerate<0,1,3>(m0.sample<0,6,27,83>());
				case 27: return maskDegenerate<0,1,2>(m0.sample<0,6,27,83>());
				case 28: return maskDegenerate<0,1,2>(m0.sample<0,6,27,83>());
				default: return m0.sample<0,6,27,83>();
			}
			default: throw std::logic_error("Undefined sampling function");
		}
	}
	RealVector<84> P3TetVal::degenerateZeroed_m0() const {
		RealVector<84> _b = m0;
		switch (degenerateState) {
			case 1: _b[83] = Real(0); break;
			case 2: _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 3: _b[27] = Real(0); break;
			case 4: _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[48] = Real(0); break;
			case 5: _b[6] = Real(0); break;
			case 6: _b[5] = Real(0); _b[6] = Real(0); _b[12] = Real(0); _b[33] = Real(0); break;
			case 7: _b[0] = Real(0); break;
			case 8: _b[0] = Real(0); _b[1] = Real(0); _b[7] = Real(0); _b[28] = Real(0); break;
			case 9: _b[27] = Real(0); _b[48] = Real(0); _b[63] = Real(0); _b[73] = Real(0); _b[79] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 10: _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 11: _b[6] = Real(0); _b[33] = Real(0); _b[53] = Real(0); _b[67] = Real(0); _b[76] = Real(0); _b[81] = Real(0); _b[83] = Real(0); break;
			case 12: _b[5] = Real(0); _b[6] = Real(0); _b[12] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[38] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[57] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[78] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 13: _b[0] = Real(0); _b[28] = Real(0); _b[49] = Real(0); _b[64] = Real(0); _b[74] = Real(0); _b[80] = Real(0); _b[83] = Real(0); break;
			case 14: _b[0] = Real(0); _b[1] = Real(0); _b[7] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[34] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[54] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[77] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 15: _b[6] = Real(0); _b[12] = Real(0); _b[17] = Real(0); _b[21] = Real(0); _b[24] = Real(0); _b[26] = Real(0); _b[27] = Real(0); break;
			case 16: _b[5] = Real(0); _b[6] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[33] = Real(0); _b[38] = Real(0); _b[42] = Real(0); _b[45] = Real(0); _b[47] = Real(0); _b[48] = Real(0); break;
			case 17: _b[0] = Real(0); _b[7] = Real(0); _b[13] = Real(0); _b[18] = Real(0); _b[22] = Real(0); _b[25] = Real(0); _b[27] = Real(0); break;
			case 18: _b[0] = Real(0); _b[1] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[34] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[46] = Real(0); _b[48] = Real(0); break;
			case 19: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); break;
			case 20: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); break;
			case 21: _b[6] = Real(0); _b[12] = Real(0); _b[17] = Real(0); _b[21] = Real(0); _b[24] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[33] = Real(0); _b[38] = Real(0); _b[42] = Real(0); _b[45] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[53] = Real(0); _b[57] = Real(0); _b[60] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[76] = Real(0); _b[78] = Real(0); _b[79] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 22: _b[5] = Real(0); _b[6] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 23: _b[0] = Real(0); _b[7] = Real(0); _b[13] = Real(0); _b[18] = Real(0); _b[22] = Real(0); _b[25] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[34] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[46] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[54] = Real(0); _b[58] = Real(0); _b[61] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[71] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[77] = Real(0); _b[79] = Real(0); _b[80] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 24: _b[0] = Real(0); _b[1] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 25: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[83] = Real(0); break;
			case 26: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[80] = Real(0); _b[81] = Real(0); _b[82] = Real(0); _b[83] = Real(0); break;
			case 27: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); break;
			case 28: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); break;
			default: break;
		}
		return _b;
	}
	template<> std::array<P3TetVal, P3TetVal::schemes[0]> P3TetVal::split_impl<0>() const {
		auto _r_m0 = subdiv_0_3p6(degenerateZeroed_m0());
		auto _r_x0 = subdiv_0_3p1(x0);
		auto _r_x1 = subdiv_0_3p1(x1);
		auto _r_x2 = subdiv_0_3p1(x2);
		return {
			P3TetVal{*this, 0,
				_r_m0[0], 
				_r_x0[0], 
				_r_x1[0], 
				_r_x2[0]
			},
			P3TetVal{*this, 1,
				_r_m0[1], 
				_r_x0[1], 
				_r_x1[1], 
				_r_x2[1]
			},
			P3TetVal{*this, 2,
				_r_m0[2], 
				_r_x0[2], 
				_r_x1[2], 
				_r_x2[2]
			},
			P3TetVal{*this, 3,
				_r_m0[3], 
				_r_x0[3], 
				_r_x1[3], 
				_r_x2[3]
			},
			P3TetVal{*this, 4,
				_r_m0[4], 
				_r_x0[4], 
				_r_x1[4], 
				_r_x2[4]
			},
			P3TetVal{*this, 5,
				_r_m0[5], 
				_r_x0[5], 
				_r_x1[5], 
				_r_x2[5]
			},
			P3TetVal{*this, 6,
				_r_m0[6], 
				_r_x0[6], 
				_r_x1[6], 
				_r_x2[6]
			},
			P3TetVal{*this, 7,
				_r_m0[7], 
				_r_x0[7], 
				_r_x1[7], 
				_r_x2[7]
			},
		};
	}
	std::ostream &operator<<(std::ostream &out, const P3TetVal &s) {
		for (unsigned i=0; i<s.numVertices; ++i) {
			out << s.getVertex(i) << ' ';
		}
		return out;
	}
}
