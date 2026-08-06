#include "../P2TetVal.hpp"
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

	unsigned P2TetVal::degenerateStateFromVertices(unsigned vertexMask, unsigned order) {
		if (vertexMask == 0u) return 0u;
		for (unsigned s=0; s<29; ++s) {
			if (kDegenerateStateVertices[s] == vertexMask && kDegenerateStateOrders[s] == order) return s;
		}
		throw std::invalid_argument("No degenerate state for this vertex set and order");
	}
	unsigned P2TetVal::degenerateStateVertexMask(unsigned s) { return kDegenerateStateVertices[s]; }
	unsigned P2TetVal::degenerateStateOrder(unsigned s) { return kDegenerateStateOrders[s]; }
	unsigned P2TetVal::degenerateTransition(unsigned s, unsigned q) { return kDegenerateTransitions[s][q]; }

	P2TetVal::P2TetVal(const P2TetVal &parent, unsigned q,
		const RealVector<20> &m0,
		const RealVector<4> &x0,
		const RealVector<4> &x1,
		const RealVector<4> &x2
	) :
	m0(m0),
	x0(x0),
	x1(x1),
	x2(x2)
	{ inherit(parent, q); }

	P2TetVal::P2TetVal(
		const RealVector<10> &px,
		const RealVector<10> &py,
		const RealVector<10> &pz
	) :
	m0(LB_3p3(CL_m0(px, py, pz))),
	x0{0, 0, 0, 1},
	x1{0, 0, 1, 0},
	x2{0, 1, 0, 0}
	{
		history = std::make_shared<SubdivHistory>();
	}

	void P2TetVal::inherit(const P2TetVal &parent, unsigned q) {
		depth = parent.depth + 1;
		history = std::make_shared<SubdivHistory>(q, parent.history);
		degenerateState = kDegenerateTransitions[parent.degenerateState][q];
	}
	RealInterval P2TetVal::inclusion(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return m0.inclusionDegenerate<19>();
				case 2: return m0.inclusionDegenerate<16,17,18,19>();
				case 3: return m0.inclusionDegenerate<9>();
				case 4: return m0.inclusionDegenerate<7,8,9,15>();
				case 5: return m0.inclusionDegenerate<3>();
				case 6: return m0.inclusionDegenerate<2,3,6,12>();
				case 7: return m0.inclusionDegenerate<0>();
				case 8: return m0.inclusionDegenerate<0,1,4,10>();
				case 9: return m0.inclusionDegenerate<9,15,18,19>();
				case 10: return m0.inclusionDegenerate<7,8,9,13,14,15,16,17,18,19>();
				case 11: return m0.inclusionDegenerate<3,12,17,19>();
				case 12: return m0.inclusionDegenerate<2,3,6,11,12,14,16,17,18,19>();
				case 13: return m0.inclusionDegenerate<0,10,16,19>();
				case 14: return m0.inclusionDegenerate<0,1,4,10,11,13,16,17,18,19>();
				case 15: return m0.inclusionDegenerate<3,6,8,9>();
				case 16: return m0.inclusionDegenerate<2,3,5,6,7,8,9,12,14,15>();
				case 17: return m0.inclusionDegenerate<0,4,7,9>();
				case 18: return m0.inclusionDegenerate<0,1,4,5,7,8,9,10,13,15>();
				case 19: return m0.inclusionDegenerate<0,1,2,3>();
				case 20: return m0.inclusionDegenerate<0,1,2,3,4,5,6,10,11,12>();
				case 21: return m0.inclusionDegenerate<3,6,8,9,12,14,15,17,18,19>();
				case 22: return m0.inclusionDegenerate<2,3,5,6,7,8,9,11,12,13,14,15,16,17,18,19>();
				case 23: return m0.inclusionDegenerate<0,4,7,9,10,13,15,16,18,19>();
				case 24: return m0.inclusionDegenerate<0,1,4,5,7,8,9,10,11,13,14,15,16,17,18,19>();
				case 25: return m0.inclusionDegenerate<0,1,2,3,10,11,12,16,17,19>();
				case 26: return m0.inclusionDegenerate<0,1,2,3,4,5,6,10,11,12,13,14,16,17,18,19>();
				case 27: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9>();
				case 28: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>();
				default: return m0.inclusion();
			}
			default: throw std::logic_error("Undefined inclusion function");
		}
	}
	RealVector<P2TetVal::numVertices> P2TetVal::sample(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return maskDegenerate<3>(m0.sample<0,3,9,19>());
				case 2: return maskDegenerate<3>(m0.sample<0,3,9,19>());
				case 3: return maskDegenerate<2>(m0.sample<0,3,9,19>());
				case 4: return maskDegenerate<2>(m0.sample<0,3,9,19>());
				case 5: return maskDegenerate<1>(m0.sample<0,3,9,19>());
				case 6: return maskDegenerate<1>(m0.sample<0,3,9,19>());
				case 7: return maskDegenerate<0>(m0.sample<0,3,9,19>());
				case 8: return maskDegenerate<0>(m0.sample<0,3,9,19>());
				case 9: return maskDegenerate<2,3>(m0.sample<0,3,9,19>());
				case 10: return maskDegenerate<2,3>(m0.sample<0,3,9,19>());
				case 11: return maskDegenerate<1,3>(m0.sample<0,3,9,19>());
				case 12: return maskDegenerate<1,3>(m0.sample<0,3,9,19>());
				case 13: return maskDegenerate<0,3>(m0.sample<0,3,9,19>());
				case 14: return maskDegenerate<0,3>(m0.sample<0,3,9,19>());
				case 15: return maskDegenerate<1,2>(m0.sample<0,3,9,19>());
				case 16: return maskDegenerate<1,2>(m0.sample<0,3,9,19>());
				case 17: return maskDegenerate<0,2>(m0.sample<0,3,9,19>());
				case 18: return maskDegenerate<0,2>(m0.sample<0,3,9,19>());
				case 19: return maskDegenerate<0,1>(m0.sample<0,3,9,19>());
				case 20: return maskDegenerate<0,1>(m0.sample<0,3,9,19>());
				case 21: return maskDegenerate<1,2,3>(m0.sample<0,3,9,19>());
				case 22: return maskDegenerate<1,2,3>(m0.sample<0,3,9,19>());
				case 23: return maskDegenerate<0,2,3>(m0.sample<0,3,9,19>());
				case 24: return maskDegenerate<0,2,3>(m0.sample<0,3,9,19>());
				case 25: return maskDegenerate<0,1,3>(m0.sample<0,3,9,19>());
				case 26: return maskDegenerate<0,1,3>(m0.sample<0,3,9,19>());
				case 27: return maskDegenerate<0,1,2>(m0.sample<0,3,9,19>());
				case 28: return maskDegenerate<0,1,2>(m0.sample<0,3,9,19>());
				default: return m0.sample<0,3,9,19>();
			}
			default: throw std::logic_error("Undefined sampling function");
		}
	}
	RealVector<20> P2TetVal::degenerateZeroed_m0() const {
		RealVector<20> _b = m0;
		switch (degenerateState) {
			case 1: _b[19] = Real(0); break;
			case 2: _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 3: _b[9] = Real(0); break;
			case 4: _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[15] = Real(0); break;
			case 5: _b[3] = Real(0); break;
			case 6: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[12] = Real(0); break;
			case 7: _b[0] = Real(0); break;
			case 8: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[10] = Real(0); break;
			case 9: _b[9] = Real(0); _b[15] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 10: _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 11: _b[3] = Real(0); _b[12] = Real(0); _b[17] = Real(0); _b[19] = Real(0); break;
			case 12: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[14] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 13: _b[0] = Real(0); _b[10] = Real(0); _b[16] = Real(0); _b[19] = Real(0); break;
			case 14: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[13] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 15: _b[3] = Real(0); _b[6] = Real(0); _b[8] = Real(0); _b[9] = Real(0); break;
			case 16: _b[2] = Real(0); _b[3] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[14] = Real(0); _b[15] = Real(0); break;
			case 17: _b[0] = Real(0); _b[4] = Real(0); _b[7] = Real(0); _b[9] = Real(0); break;
			case 18: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[13] = Real(0); _b[15] = Real(0); break;
			case 19: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); break;
			case 20: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); break;
			case 21: _b[3] = Real(0); _b[6] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 22: _b[2] = Real(0); _b[3] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 23: _b[0] = Real(0); _b[4] = Real(0); _b[7] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[13] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 24: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 25: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[19] = Real(0); break;
			case 26: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); break;
			case 27: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); break;
			case 28: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); break;
			default: break;
		}
		return _b;
	}
	template<> std::array<P2TetVal, P2TetVal::schemes[0]> P2TetVal::split_impl<0>() const {
		auto _r_m0 = subdiv_0_3p3(degenerateZeroed_m0());
		auto _r_x0 = subdiv_0_3p1(x0);
		auto _r_x1 = subdiv_0_3p1(x1);
		auto _r_x2 = subdiv_0_3p1(x2);
		return {
			P2TetVal{*this, 0,
				_r_m0[0], 
				_r_x0[0], 
				_r_x1[0], 
				_r_x2[0]
			},
			P2TetVal{*this, 1,
				_r_m0[1], 
				_r_x0[1], 
				_r_x1[1], 
				_r_x2[1]
			},
			P2TetVal{*this, 2,
				_r_m0[2], 
				_r_x0[2], 
				_r_x1[2], 
				_r_x2[2]
			},
			P2TetVal{*this, 3,
				_r_m0[3], 
				_r_x0[3], 
				_r_x1[3], 
				_r_x2[3]
			},
			P2TetVal{*this, 4,
				_r_m0[4], 
				_r_x0[4], 
				_r_x1[4], 
				_r_x2[4]
			},
			P2TetVal{*this, 5,
				_r_m0[5], 
				_r_x0[5], 
				_r_x1[5], 
				_r_x2[5]
			},
			P2TetVal{*this, 6,
				_r_m0[6], 
				_r_x0[6], 
				_r_x1[6], 
				_r_x2[6]
			},
			P2TetVal{*this, 7,
				_r_m0[7], 
				_r_x0[7], 
				_r_x1[7], 
				_r_x2[7]
			},
		};
	}
	std::ostream &operator<<(std::ostream &out, const P2TetVal &s) {
		for (unsigned i=0; i<s.numVertices; ++i) {
			out << s.getVertex(i) << ' ';
		}
		return out;
	}
}
