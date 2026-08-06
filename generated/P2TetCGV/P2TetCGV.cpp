#include "../P2TetCGV.hpp"
#include <stdexcept>
namespace miso {
	namespace {
		constexpr std::array<unsigned, 89> kDegenerateStateVertices = {0u, 128u, 128u, 64u, 64u, 192u, 192u, 32u, 32u, 16u, 16u, 48u, 48u, 8u, 8u, 4u, 4u, 12u, 12u, 2u, 2u, 1u, 1u, 3u, 3u, 160u, 160u, 80u, 80u, 240u, 240u, 136u, 136u, 68u, 68u, 204u, 204u, 130u, 130u, 65u, 65u, 195u, 195u, 40u, 40u, 20u, 20u, 60u, 60u, 34u, 34u, 17u, 17u, 51u, 51u, 10u, 10u, 5u, 5u, 15u, 15u, 168u, 168u, 84u, 84u, 252u, 252u, 162u, 162u, 81u, 81u, 243u, 243u, 138u, 138u, 69u, 69u, 207u, 207u, 42u, 42u, 21u, 21u, 63u, 63u, 170u, 170u, 85u, 85u};
		constexpr std::array<unsigned, 89> kDegenerateStateOrders = {0u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u, 1u, 2u};
		constexpr std::array<std::array<unsigned, 18>, 89> kDegenerateTransitions = {{
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
			{0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
			{0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
			{0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5},
			{0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6},
			{0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
			{0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
			{0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0},
			{0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0},
			{0, 0, 0, 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11},
			{0, 0, 0, 0, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 12},
			{0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
			{0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14},
			{0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0},
			{0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0},
			{0, 0, 0, 0, 0, 0, 17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17},
			{0, 0, 0, 0, 0, 0, 18, 18, 0, 0, 0, 0, 0, 0, 0, 0, 18, 18},
			{0, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19},
			{0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20},
			{21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0},
			{22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 0},
			{23, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 23},
			{24, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24},
			{0, 0, 0, 25, 0, 25, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1, 0, 25},
			{0, 0, 0, 26, 0, 26, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2, 0, 26},
			{0, 0, 27, 0, 27, 0, 0, 0, 0, 0, 9, 0, 0, 0, 3, 0, 27, 0},
			{0, 0, 28, 0, 28, 0, 0, 0, 0, 0, 10, 0, 0, 0, 4, 0, 28, 0},
			{0, 0, 29, 29, 29, 29, 0, 0, 0, 0, 11, 11, 0, 0, 5, 5, 29, 29},
			{0, 0, 30, 30, 30, 30, 0, 0, 0, 0, 12, 12, 0, 0, 6, 6, 30, 30},
			{0, 0, 0, 31, 0, 0, 0, 31, 0, 13, 0, 13, 0, 7, 0, 7, 0, 31},
			{0, 0, 0, 32, 0, 0, 0, 32, 0, 14, 0, 14, 0, 8, 0, 8, 0, 32},
			{0, 0, 33, 0, 0, 0, 33, 0, 15, 0, 15, 0, 9, 0, 9, 0, 33, 0},
			{0, 0, 34, 0, 0, 0, 34, 0, 16, 0, 16, 0, 10, 0, 10, 0, 34, 0},
			{0, 0, 35, 35, 0, 0, 35, 35, 17, 17, 17, 17, 11, 11, 11, 11, 35, 35},
			{0, 0, 36, 36, 0, 0, 36, 36, 18, 18, 18, 18, 12, 12, 12, 12, 36, 36},
			{0, 37, 0, 37, 0, 0, 0, 0, 0, 19, 0, 19, 0, 0, 0, 0, 0, 37},
			{0, 38, 0, 38, 0, 0, 0, 0, 0, 20, 0, 20, 0, 0, 0, 0, 0, 38},
			{39, 0, 39, 0, 0, 0, 0, 0, 21, 0, 21, 0, 0, 0, 0, 0, 39, 0},
			{40, 0, 40, 0, 0, 0, 0, 0, 22, 0, 22, 0, 0, 0, 0, 0, 40, 0},
			{41, 41, 41, 41, 0, 0, 0, 0, 23, 23, 23, 23, 0, 0, 0, 0, 41, 41},
			{42, 42, 42, 42, 0, 0, 0, 0, 24, 24, 24, 24, 0, 0, 0, 0, 42, 42},
			{0, 0, 0, 0, 0, 43, 0, 43, 0, 0, 0, 0, 0, 13, 0, 13, 0, 43},
			{0, 0, 0, 0, 0, 44, 0, 44, 0, 0, 0, 0, 0, 14, 0, 14, 0, 44},
			{0, 0, 0, 0, 45, 0, 45, 0, 0, 0, 0, 0, 15, 0, 15, 0, 45, 0},
			{0, 0, 0, 0, 46, 0, 46, 0, 0, 0, 0, 0, 16, 0, 16, 0, 46, 0},
			{0, 0, 0, 0, 47, 47, 47, 47, 0, 0, 0, 0, 17, 17, 17, 17, 47, 47},
			{0, 0, 0, 0, 48, 48, 48, 48, 0, 0, 0, 0, 18, 18, 18, 18, 48, 48},
			{0, 49, 0, 0, 0, 49, 0, 0, 0, 1, 0, 1, 0, 19, 0, 19, 0, 49},
			{0, 50, 0, 0, 0, 50, 0, 0, 0, 2, 0, 2, 0, 20, 0, 20, 0, 50},
			{51, 0, 0, 0, 51, 0, 0, 0, 3, 0, 3, 0, 21, 0, 21, 0, 51, 0},
			{52, 0, 0, 0, 52, 0, 0, 0, 4, 0, 4, 0, 22, 0, 22, 0, 52, 0},
			{53, 53, 0, 0, 53, 53, 0, 0, 5, 5, 5, 5, 23, 23, 23, 23, 53, 53},
			{54, 54, 0, 0, 54, 54, 0, 0, 6, 6, 6, 6, 24, 24, 24, 24, 54, 54},
			{0, 55, 0, 0, 0, 0, 0, 55, 0, 7, 0, 0, 0, 1, 0, 0, 0, 55},
			{0, 56, 0, 0, 0, 0, 0, 56, 0, 8, 0, 0, 0, 2, 0, 0, 0, 56},
			{57, 0, 0, 0, 0, 0, 57, 0, 9, 0, 0, 0, 3, 0, 0, 0, 57, 0},
			{58, 0, 0, 0, 0, 0, 58, 0, 10, 0, 0, 0, 4, 0, 0, 0, 58, 0},
			{59, 59, 0, 0, 0, 0, 59, 59, 11, 11, 0, 0, 5, 5, 0, 0, 59, 59},
			{60, 60, 0, 0, 0, 0, 60, 60, 12, 12, 0, 0, 6, 6, 0, 0, 60, 60},
			{0, 0, 0, 61, 0, 61, 0, 61, 0, 13, 0, 43, 0, 43, 0, 61, 0, 61},
			{0, 0, 0, 62, 0, 62, 0, 62, 0, 14, 0, 44, 0, 44, 0, 62, 0, 62},
			{0, 0, 63, 0, 63, 0, 63, 0, 15, 0, 45, 0, 45, 0, 63, 0, 63, 0},
			{0, 0, 64, 0, 64, 0, 64, 0, 16, 0, 46, 0, 46, 0, 64, 0, 64, 0},
			{0, 0, 65, 65, 65, 65, 65, 65, 17, 17, 47, 47, 47, 47, 65, 65, 65, 65},
			{0, 0, 66, 66, 66, 66, 66, 66, 18, 18, 48, 48, 48, 48, 66, 66, 66, 66},
			{0, 67, 0, 67, 0, 67, 0, 0, 0, 37, 0, 67, 0, 19, 0, 37, 0, 67},
			{0, 68, 0, 68, 0, 68, 0, 0, 0, 38, 0, 68, 0, 20, 0, 38, 0, 68},
			{69, 0, 69, 0, 69, 0, 0, 0, 39, 0, 69, 0, 21, 0, 39, 0, 69, 0},
			{70, 0, 70, 0, 70, 0, 0, 0, 40, 0, 70, 0, 22, 0, 40, 0, 70, 0},
			{71, 71, 71, 71, 71, 71, 0, 0, 41, 41, 71, 71, 23, 23, 41, 41, 71, 71},
			{72, 72, 72, 72, 72, 72, 0, 0, 42, 42, 72, 72, 24, 24, 42, 42, 72, 72},
			{0, 73, 0, 73, 0, 0, 0, 73, 0, 79, 0, 55, 0, 25, 0, 7, 0, 73},
			{0, 74, 0, 74, 0, 0, 0, 74, 0, 80, 0, 56, 0, 26, 0, 8, 0, 74},
			{75, 0, 75, 0, 0, 0, 75, 0, 81, 0, 57, 0, 27, 0, 9, 0, 75, 0},
			{76, 0, 76, 0, 0, 0, 76, 0, 82, 0, 58, 0, 28, 0, 10, 0, 76, 0},
			{77, 77, 77, 77, 0, 0, 77, 77, 83, 83, 59, 59, 29, 29, 11, 11, 77, 77},
			{78, 78, 78, 78, 0, 0, 78, 78, 84, 84, 60, 60, 30, 30, 12, 12, 78, 78},
			{0, 79, 0, 0, 0, 79, 0, 79, 0, 25, 0, 1, 0, 73, 0, 55, 0, 79},
			{0, 80, 0, 0, 0, 80, 0, 80, 0, 26, 0, 2, 0, 74, 0, 56, 0, 80},
			{81, 0, 0, 0, 81, 0, 81, 0, 27, 0, 3, 0, 75, 0, 57, 0, 81, 0},
			{82, 0, 0, 0, 82, 0, 82, 0, 28, 0, 4, 0, 76, 0, 58, 0, 82, 0},
			{83, 83, 0, 0, 83, 83, 83, 83, 29, 29, 5, 5, 77, 77, 59, 59, 83, 83},
			{84, 84, 0, 0, 84, 84, 84, 84, 30, 30, 6, 6, 78, 78, 60, 60, 84, 84},
			{0, 85, 0, 85, 0, 85, 0, 85, 0, 85, 0, 85, 0, 85, 0, 85, 0, 85},
			{0, 86, 0, 86, 0, 86, 0, 86, 0, 86, 0, 86, 0, 86, 0, 86, 0, 86},
			{87, 0, 87, 0, 87, 0, 87, 0, 87, 0, 87, 0, 87, 0, 87, 0, 87, 0},
			{88, 0, 88, 0, 88, 0, 88, 0, 88, 0, 88, 0, 88, 0, 88, 0, 88, 0},
		}};
	}

	unsigned P2TetCGV::degenerateStateFromVertices(unsigned vertexMask, unsigned order) {
		if (vertexMask == 0u) return 0u;
		for (unsigned s=0; s<89; ++s) {
			if (kDegenerateStateVertices[s] == vertexMask && kDegenerateStateOrders[s] == order) return s;
		}
		throw std::invalid_argument("No degenerate state for this vertex set and order");
	}
	unsigned P2TetCGV::degenerateStateVertexMask(unsigned s) { return kDegenerateStateVertices[s]; }
	unsigned P2TetCGV::degenerateStateOrder(unsigned s) { return kDegenerateStateOrders[s]; }
	unsigned P2TetCGV::degenerateTransition(unsigned s, unsigned q) { return kDegenerateTransitions[s][q]; }

	P2TetCGV::P2TetCGV(const P2TetCGV &parent, unsigned q,
		const RealVector<80> &m0,
		const RealVector<8> &x0,
		const RealVector<8> &x1,
		const RealVector<8> &x2,
		const RealVector<8> &x3
	) :
	m0(m0),
	x0(x0),
	x1(x1),
	x2(x2),
	x3(x3)
	{ inherit(parent, q); }

	P2TetCGV::P2TetCGV(
		const RealVector<10> &p0x,
		const RealVector<10> &p0y,
		const RealVector<10> &p0z,
		const RealVector<10> &p1x,
		const RealVector<10> &p1y,
		const RealVector<10> &p1z
	) :
	m0(LB_3p3_1p3(CL_m0(p0x, p0y, p0z, p1x, p1y, p1z))),
	x0{0, 0, 0, 0, 0, 0, 1, 1},
	x1{0, 0, 0, 0, 1, 1, 0, 0},
	x2{0, 0, 1, 1, 0, 0, 0, 0},
	x3{0, 1, 0, 1, 0, 1, 0, 1}
	{
		history = std::make_shared<SubdivHistory>();
	}

	void P2TetCGV::inherit(const P2TetCGV &parent, unsigned q) {
		depth = parent.depth + 1;
		history = std::make_shared<SubdivHistory>(q, parent.history);
		degenerateState = kDegenerateTransitions[parent.degenerateState][q];
	}
	RealInterval P2TetCGV::inclusion(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return m0.inclusionDegenerate<79>();
				case 2: return m0.inclusionDegenerate<67,71,75,78,79>();
				case 3: return m0.inclusionDegenerate<76>();
				case 4: return m0.inclusionDegenerate<64,68,72,76,77>();
				case 5: return m0.inclusionDegenerate<76,77,78,79>();
				case 6: return m0.inclusionDegenerate<64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 7: return m0.inclusionDegenerate<39>();
				case 8: return m0.inclusionDegenerate<31,35,38,39,63>();
				case 9: return m0.inclusionDegenerate<36>();
				case 10: return m0.inclusionDegenerate<28,32,36,37,60>();
				case 11: return m0.inclusionDegenerate<36,37,38,39>();
				case 12: return m0.inclusionDegenerate<28,29,30,31,32,33,34,35,36,37,38,39,60,61,62,63>();
				case 13: return m0.inclusionDegenerate<15>();
				case 14: return m0.inclusionDegenerate<11,14,15,27,51>();
				case 15: return m0.inclusionDegenerate<12>();
				case 16: return m0.inclusionDegenerate<8,12,13,24,48>();
				case 17: return m0.inclusionDegenerate<12,13,14,15>();
				case 18: return m0.inclusionDegenerate<8,9,10,11,12,13,14,15,24,25,26,27,48,49,50,51>();
				case 19: return m0.inclusionDegenerate<3>();
				case 20: return m0.inclusionDegenerate<2,3,7,19,43>();
				case 21: return m0.inclusionDegenerate<0>();
				case 22: return m0.inclusionDegenerate<0,1,4,16,40>();
				case 23: return m0.inclusionDegenerate<0,1,2,3>();
				case 24: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,16,17,18,19,40,41,42,43>();
				case 25: return m0.inclusionDegenerate<39,63,75,79>();
				case 26: return m0.inclusionDegenerate<31,35,38,39,55,59,62,63,67,71,74,75,78,79>();
				case 27: return m0.inclusionDegenerate<36,60,72,76>();
				case 28: return m0.inclusionDegenerate<28,32,36,37,52,56,60,61,64,68,72,73,76,77>();
				case 29: return m0.inclusionDegenerate<36,37,38,39,60,61,62,63,72,73,74,75,76,77,78,79>();
				case 30: return m0.inclusionDegenerate<28,29,30,31,32,33,34,35,36,37,38,39,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 31: return m0.inclusionDegenerate<15,51,71,79>();
				case 32: return m0.inclusionDegenerate<11,14,15,27,47,50,51,59,67,70,71,75,78,79>();
				case 33: return m0.inclusionDegenerate<12,48,68,76>();
				case 34: return m0.inclusionDegenerate<8,12,13,24,44,48,49,56,64,68,69,72,76,77>();
				case 35: return m0.inclusionDegenerate<12,13,14,15,48,49,50,51,68,69,70,71,76,77,78,79>();
				case 36: return m0.inclusionDegenerate<8,9,10,11,12,13,14,15,24,25,26,27,44,45,46,47,48,49,50,51,56,57,58,59,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 37: return m0.inclusionDegenerate<3,43,67,79>();
				case 38: return m0.inclusionDegenerate<2,3,7,19,42,43,47,55,66,67,71,75,78,79>();
				case 39: return m0.inclusionDegenerate<0,40,64,76>();
				case 40: return m0.inclusionDegenerate<0,1,4,16,40,41,44,52,64,65,68,72,76,77>();
				case 41: return m0.inclusionDegenerate<0,1,2,3,40,41,42,43,64,65,66,67,76,77,78,79>();
				case 42: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,16,17,18,19,40,41,42,43,44,45,46,47,52,53,54,55,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 43: return m0.inclusionDegenerate<15,27,35,39>();
				case 44: return m0.inclusionDegenerate<11,14,15,23,26,27,31,34,35,38,39,51,59,63>();
				case 45: return m0.inclusionDegenerate<12,24,32,36>();
				case 46: return m0.inclusionDegenerate<8,12,13,20,24,25,28,32,33,36,37,48,56,60>();
				case 47: return m0.inclusionDegenerate<12,13,14,15,24,25,26,27,32,33,34,35,36,37,38,39>();
				case 48: return m0.inclusionDegenerate<8,9,10,11,12,13,14,15,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,48,49,50,51,56,57,58,59,60,61,62,63>();
				case 49: return m0.inclusionDegenerate<3,19,31,39>();
				case 50: return m0.inclusionDegenerate<2,3,7,18,19,23,30,31,35,38,39,43,55,63>();
				case 51: return m0.inclusionDegenerate<0,16,28,36>();
				case 52: return m0.inclusionDegenerate<0,1,4,16,17,20,28,29,32,36,37,40,52,60>();
				case 53: return m0.inclusionDegenerate<0,1,2,3,16,17,18,19,28,29,30,31,36,37,38,39>();
				case 54: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,16,17,18,19,20,21,22,23,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,52,53,54,55,60,61,62,63>();
				case 55: return m0.inclusionDegenerate<3,7,11,15>();
				case 56: return m0.inclusionDegenerate<2,3,6,7,10,11,14,15,19,23,27,43,47,51>();
				case 57: return m0.inclusionDegenerate<0,4,8,12>();
				case 58: return m0.inclusionDegenerate<0,1,4,5,8,9,12,13,16,20,24,40,44,48>();
				case 59: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>();
				case 60: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,40,41,42,43,44,45,46,47,48,49,50,51>();
				case 61: return m0.inclusionDegenerate<15,27,35,39,51,59,63,71,75,79>();
				case 62: return m0.inclusionDegenerate<11,14,15,23,26,27,31,34,35,38,39,47,50,51,55,58,59,62,63,67,70,71,74,75,78,79>();
				case 63: return m0.inclusionDegenerate<12,24,32,36,48,56,60,68,72,76>();
				case 64: return m0.inclusionDegenerate<8,12,13,20,24,25,28,32,33,36,37,44,48,49,52,56,57,60,61,64,68,69,72,73,76,77>();
				case 65: return m0.inclusionDegenerate<12,13,14,15,24,25,26,27,32,33,34,35,36,37,38,39,48,49,50,51,56,57,58,59,60,61,62,63,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 66: return m0.inclusionDegenerate<8,9,10,11,12,13,14,15,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 67: return m0.inclusionDegenerate<3,19,31,39,43,55,63,67,75,79>();
				case 68: return m0.inclusionDegenerate<2,3,7,18,19,23,30,31,35,38,39,42,43,47,54,55,59,62,63,66,67,71,74,75,78,79>();
				case 69: return m0.inclusionDegenerate<0,16,28,36,40,52,60,64,72,76>();
				case 70: return m0.inclusionDegenerate<0,1,4,16,17,20,28,29,32,36,37,40,41,44,52,53,56,60,61,64,65,68,72,73,76,77>();
				case 71: return m0.inclusionDegenerate<0,1,2,3,16,17,18,19,28,29,30,31,36,37,38,39,40,41,42,43,52,53,54,55,60,61,62,63,64,65,66,67,72,73,74,75,76,77,78,79>();
				case 72: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,16,17,18,19,20,21,22,23,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 73: return m0.inclusionDegenerate<3,7,11,15,43,47,51,67,71,79>();
				case 74: return m0.inclusionDegenerate<2,3,6,7,10,11,14,15,19,23,27,42,43,46,47,50,51,55,59,66,67,70,71,75,78,79>();
				case 75: return m0.inclusionDegenerate<0,4,8,12,40,44,48,64,68,76>();
				case 76: return m0.inclusionDegenerate<0,1,4,5,8,9,12,13,16,20,24,40,41,44,45,48,49,52,56,64,65,68,69,72,76,77>();
				case 77: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,40,41,42,43,44,45,46,47,48,49,50,51,64,65,66,67,68,69,70,71,76,77,78,79>();
				case 78: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79>();
				case 79: return m0.inclusionDegenerate<3,7,11,15,19,23,27,31,35,39>();
				case 80: return m0.inclusionDegenerate<2,3,6,7,10,11,14,15,18,19,22,23,26,27,30,31,34,35,38,39,43,47,51,55,59,63>();
				case 81: return m0.inclusionDegenerate<0,4,8,12,16,20,24,28,32,36>();
				case 82: return m0.inclusionDegenerate<0,1,4,5,8,9,12,13,16,17,20,21,24,25,28,29,32,33,36,37,40,44,48,52,56,60>();
				case 83: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39>();
				case 84: return m0.inclusionDegenerate<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63>();
				case 85: return m0.inclusionDegenerate<3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63,67,71,75,79>();
				case 86: return m0.inclusionDegenerate<2,3,6,7,10,11,14,15,18,19,22,23,26,27,30,31,34,35,38,39,42,43,46,47,50,51,54,55,58,59,62,63,66,67,70,71,74,75,78,79>();
				case 87: return m0.inclusionDegenerate<0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76>();
				case 88: return m0.inclusionDegenerate<0,1,4,5,8,9,12,13,16,17,20,21,24,25,28,29,32,33,36,37,40,41,44,45,48,49,52,53,56,57,60,61,64,65,68,69,72,73,76,77>();
				default: return m0.inclusion();
			}
			case 1: return x3.inclusion();
			default: throw std::logic_error("Undefined inclusion function");
		}
	}
	RealVector<P2TetCGV::numVertices> P2TetCGV::sample(unsigned i) const {
		switch (i) {
			case 0:
			switch (degenerateState) {
				case 1: return maskDegenerate<7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 2: return maskDegenerate<7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 3: return maskDegenerate<6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 4: return maskDegenerate<6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 5: return maskDegenerate<6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 6: return maskDegenerate<6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 7: return maskDegenerate<5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 8: return maskDegenerate<5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 9: return maskDegenerate<4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 10: return maskDegenerate<4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 11: return maskDegenerate<4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 12: return maskDegenerate<4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 13: return maskDegenerate<3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 14: return maskDegenerate<3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 15: return maskDegenerate<2>(m0.sample<0,3,12,15,36,39,76,79>());
				case 16: return maskDegenerate<2>(m0.sample<0,3,12,15,36,39,76,79>());
				case 17: return maskDegenerate<2,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 18: return maskDegenerate<2,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 19: return maskDegenerate<1>(m0.sample<0,3,12,15,36,39,76,79>());
				case 20: return maskDegenerate<1>(m0.sample<0,3,12,15,36,39,76,79>());
				case 21: return maskDegenerate<0>(m0.sample<0,3,12,15,36,39,76,79>());
				case 22: return maskDegenerate<0>(m0.sample<0,3,12,15,36,39,76,79>());
				case 23: return maskDegenerate<0,1>(m0.sample<0,3,12,15,36,39,76,79>());
				case 24: return maskDegenerate<0,1>(m0.sample<0,3,12,15,36,39,76,79>());
				case 25: return maskDegenerate<5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 26: return maskDegenerate<5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 27: return maskDegenerate<4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 28: return maskDegenerate<4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 29: return maskDegenerate<4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 30: return maskDegenerate<4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 31: return maskDegenerate<3,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 32: return maskDegenerate<3,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 33: return maskDegenerate<2,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 34: return maskDegenerate<2,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 35: return maskDegenerate<2,3,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 36: return maskDegenerate<2,3,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 37: return maskDegenerate<1,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 38: return maskDegenerate<1,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 39: return maskDegenerate<0,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 40: return maskDegenerate<0,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 41: return maskDegenerate<0,1,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 42: return maskDegenerate<0,1,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 43: return maskDegenerate<3,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 44: return maskDegenerate<3,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 45: return maskDegenerate<2,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 46: return maskDegenerate<2,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 47: return maskDegenerate<2,3,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 48: return maskDegenerate<2,3,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 49: return maskDegenerate<1,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 50: return maskDegenerate<1,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 51: return maskDegenerate<0,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 52: return maskDegenerate<0,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 53: return maskDegenerate<0,1,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 54: return maskDegenerate<0,1,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 55: return maskDegenerate<1,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 56: return maskDegenerate<1,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 57: return maskDegenerate<0,2>(m0.sample<0,3,12,15,36,39,76,79>());
				case 58: return maskDegenerate<0,2>(m0.sample<0,3,12,15,36,39,76,79>());
				case 59: return maskDegenerate<0,1,2,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 60: return maskDegenerate<0,1,2,3>(m0.sample<0,3,12,15,36,39,76,79>());
				case 61: return maskDegenerate<3,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 62: return maskDegenerate<3,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 63: return maskDegenerate<2,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 64: return maskDegenerate<2,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 65: return maskDegenerate<2,3,4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 66: return maskDegenerate<2,3,4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 67: return maskDegenerate<1,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 68: return maskDegenerate<1,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 69: return maskDegenerate<0,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 70: return maskDegenerate<0,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 71: return maskDegenerate<0,1,4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 72: return maskDegenerate<0,1,4,5,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 73: return maskDegenerate<1,3,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 74: return maskDegenerate<1,3,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 75: return maskDegenerate<0,2,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 76: return maskDegenerate<0,2,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 77: return maskDegenerate<0,1,2,3,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 78: return maskDegenerate<0,1,2,3,6,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 79: return maskDegenerate<1,3,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 80: return maskDegenerate<1,3,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 81: return maskDegenerate<0,2,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 82: return maskDegenerate<0,2,4>(m0.sample<0,3,12,15,36,39,76,79>());
				case 83: return maskDegenerate<0,1,2,3,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 84: return maskDegenerate<0,1,2,3,4,5>(m0.sample<0,3,12,15,36,39,76,79>());
				case 85: return maskDegenerate<1,3,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 86: return maskDegenerate<1,3,5,7>(m0.sample<0,3,12,15,36,39,76,79>());
				case 87: return maskDegenerate<0,2,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				case 88: return maskDegenerate<0,2,4,6>(m0.sample<0,3,12,15,36,39,76,79>());
				default: return m0.sample<0,3,12,15,36,39,76,79>();
			}
			case 1: return x3.sample<0,1,2,3,4,5,6,7>();
			default: throw std::logic_error("Undefined sampling function");
		}
	}
	RealVector<80> P2TetCGV::degenerateZeroed_m0() const {
		RealVector<80> _b = m0;
		switch (degenerateState) {
			case 1: _b[79] = Real(0); break;
			case 2: _b[67] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 3: _b[76] = Real(0); break;
			case 4: _b[64] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 5: _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 6: _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 7: _b[39] = Real(0); break;
			case 8: _b[31] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[63] = Real(0); break;
			case 9: _b[36] = Real(0); break;
			case 10: _b[28] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[60] = Real(0); break;
			case 11: _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); break;
			case 12: _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); break;
			case 13: _b[15] = Real(0); break;
			case 14: _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[27] = Real(0); _b[51] = Real(0); break;
			case 15: _b[12] = Real(0); break;
			case 16: _b[8] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[24] = Real(0); _b[48] = Real(0); break;
			case 17: _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); break;
			case 18: _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); break;
			case 19: _b[3] = Real(0); break;
			case 20: _b[2] = Real(0); _b[3] = Real(0); _b[7] = Real(0); _b[19] = Real(0); _b[43] = Real(0); break;
			case 21: _b[0] = Real(0); break;
			case 22: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[16] = Real(0); _b[40] = Real(0); break;
			case 23: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); break;
			case 24: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); break;
			case 25: _b[39] = Real(0); _b[63] = Real(0); _b[75] = Real(0); _b[79] = Real(0); break;
			case 26: _b[31] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[55] = Real(0); _b[59] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[67] = Real(0); _b[71] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 27: _b[36] = Real(0); _b[60] = Real(0); _b[72] = Real(0); _b[76] = Real(0); break;
			case 28: _b[28] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[52] = Real(0); _b[56] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 29: _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 30: _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 31: _b[15] = Real(0); _b[51] = Real(0); _b[71] = Real(0); _b[79] = Real(0); break;
			case 32: _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[27] = Real(0); _b[47] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[59] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 33: _b[12] = Real(0); _b[48] = Real(0); _b[68] = Real(0); _b[76] = Real(0); break;
			case 34: _b[8] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[24] = Real(0); _b[44] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[56] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[72] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 35: _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 36: _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 37: _b[3] = Real(0); _b[43] = Real(0); _b[67] = Real(0); _b[79] = Real(0); break;
			case 38: _b[2] = Real(0); _b[3] = Real(0); _b[7] = Real(0); _b[19] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[55] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 39: _b[0] = Real(0); _b[40] = Real(0); _b[64] = Real(0); _b[76] = Real(0); break;
			case 40: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[16] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[44] = Real(0); _b[52] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 41: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 42: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 43: _b[15] = Real(0); _b[27] = Real(0); _b[35] = Real(0); _b[39] = Real(0); break;
			case 44: _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[23] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[31] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[51] = Real(0); _b[59] = Real(0); _b[63] = Real(0); break;
			case 45: _b[12] = Real(0); _b[24] = Real(0); _b[32] = Real(0); _b[36] = Real(0); break;
			case 46: _b[8] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[28] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[48] = Real(0); _b[56] = Real(0); _b[60] = Real(0); break;
			case 47: _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); break;
			case 48: _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); break;
			case 49: _b[3] = Real(0); _b[19] = Real(0); _b[31] = Real(0); _b[39] = Real(0); break;
			case 50: _b[2] = Real(0); _b[3] = Real(0); _b[7] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[55] = Real(0); _b[63] = Real(0); break;
			case 51: _b[0] = Real(0); _b[16] = Real(0); _b[28] = Real(0); _b[36] = Real(0); break;
			case 52: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[40] = Real(0); _b[52] = Real(0); _b[60] = Real(0); break;
			case 53: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); break;
			case 54: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); break;
			case 55: _b[3] = Real(0); _b[7] = Real(0); _b[11] = Real(0); _b[15] = Real(0); break;
			case 56: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[27] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[51] = Real(0); break;
			case 57: _b[0] = Real(0); _b[4] = Real(0); _b[8] = Real(0); _b[12] = Real(0); break;
			case 58: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[16] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[40] = Real(0); _b[44] = Real(0); _b[48] = Real(0); break;
			case 59: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); break;
			case 60: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); break;
			case 61: _b[15] = Real(0); _b[27] = Real(0); _b[35] = Real(0); _b[39] = Real(0); _b[51] = Real(0); _b[59] = Real(0); _b[63] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[79] = Real(0); break;
			case 62: _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[23] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[31] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[47] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[55] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 63: _b[12] = Real(0); _b[24] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[48] = Real(0); _b[56] = Real(0); _b[60] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[76] = Real(0); break;
			case 64: _b[8] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[28] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[44] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[52] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 65: _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 66: _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 67: _b[3] = Real(0); _b[19] = Real(0); _b[31] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[55] = Real(0); _b[63] = Real(0); _b[67] = Real(0); _b[75] = Real(0); _b[79] = Real(0); break;
			case 68: _b[2] = Real(0); _b[3] = Real(0); _b[7] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[59] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[71] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 69: _b[0] = Real(0); _b[16] = Real(0); _b[28] = Real(0); _b[36] = Real(0); _b[40] = Real(0); _b[52] = Real(0); _b[60] = Real(0); _b[64] = Real(0); _b[72] = Real(0); _b[76] = Real(0); break;
			case 70: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[44] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[56] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 71: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 72: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 73: _b[3] = Real(0); _b[7] = Real(0); _b[11] = Real(0); _b[15] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[51] = Real(0); _b[67] = Real(0); _b[71] = Real(0); _b[79] = Real(0); break;
			case 74: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[27] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[55] = Real(0); _b[59] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 75: _b[0] = Real(0); _b[4] = Real(0); _b[8] = Real(0); _b[12] = Real(0); _b[40] = Real(0); _b[44] = Real(0); _b[48] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[76] = Real(0); break;
			case 76: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[16] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[52] = Real(0); _b[56] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[72] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			case 77: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 78: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[76] = Real(0); _b[77] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 79: _b[3] = Real(0); _b[7] = Real(0); _b[11] = Real(0); _b[15] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[27] = Real(0); _b[31] = Real(0); _b[35] = Real(0); _b[39] = Real(0); break;
			case 80: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[51] = Real(0); _b[55] = Real(0); _b[59] = Real(0); _b[63] = Real(0); break;
			case 81: _b[0] = Real(0); _b[4] = Real(0); _b[8] = Real(0); _b[12] = Real(0); _b[16] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[28] = Real(0); _b[32] = Real(0); _b[36] = Real(0); break;
			case 82: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[40] = Real(0); _b[44] = Real(0); _b[48] = Real(0); _b[52] = Real(0); _b[56] = Real(0); _b[60] = Real(0); break;
			case 83: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); break;
			case 84: _b[0] = Real(0); _b[1] = Real(0); _b[2] = Real(0); _b[3] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[62] = Real(0); _b[63] = Real(0); break;
			case 85: _b[3] = Real(0); _b[7] = Real(0); _b[11] = Real(0); _b[15] = Real(0); _b[19] = Real(0); _b[23] = Real(0); _b[27] = Real(0); _b[31] = Real(0); _b[35] = Real(0); _b[39] = Real(0); _b[43] = Real(0); _b[47] = Real(0); _b[51] = Real(0); _b[55] = Real(0); _b[59] = Real(0); _b[63] = Real(0); _b[67] = Real(0); _b[71] = Real(0); _b[75] = Real(0); _b[79] = Real(0); break;
			case 86: _b[2] = Real(0); _b[3] = Real(0); _b[6] = Real(0); _b[7] = Real(0); _b[10] = Real(0); _b[11] = Real(0); _b[14] = Real(0); _b[15] = Real(0); _b[18] = Real(0); _b[19] = Real(0); _b[22] = Real(0); _b[23] = Real(0); _b[26] = Real(0); _b[27] = Real(0); _b[30] = Real(0); _b[31] = Real(0); _b[34] = Real(0); _b[35] = Real(0); _b[38] = Real(0); _b[39] = Real(0); _b[42] = Real(0); _b[43] = Real(0); _b[46] = Real(0); _b[47] = Real(0); _b[50] = Real(0); _b[51] = Real(0); _b[54] = Real(0); _b[55] = Real(0); _b[58] = Real(0); _b[59] = Real(0); _b[62] = Real(0); _b[63] = Real(0); _b[66] = Real(0); _b[67] = Real(0); _b[70] = Real(0); _b[71] = Real(0); _b[74] = Real(0); _b[75] = Real(0); _b[78] = Real(0); _b[79] = Real(0); break;
			case 87: _b[0] = Real(0); _b[4] = Real(0); _b[8] = Real(0); _b[12] = Real(0); _b[16] = Real(0); _b[20] = Real(0); _b[24] = Real(0); _b[28] = Real(0); _b[32] = Real(0); _b[36] = Real(0); _b[40] = Real(0); _b[44] = Real(0); _b[48] = Real(0); _b[52] = Real(0); _b[56] = Real(0); _b[60] = Real(0); _b[64] = Real(0); _b[68] = Real(0); _b[72] = Real(0); _b[76] = Real(0); break;
			case 88: _b[0] = Real(0); _b[1] = Real(0); _b[4] = Real(0); _b[5] = Real(0); _b[8] = Real(0); _b[9] = Real(0); _b[12] = Real(0); _b[13] = Real(0); _b[16] = Real(0); _b[17] = Real(0); _b[20] = Real(0); _b[21] = Real(0); _b[24] = Real(0); _b[25] = Real(0); _b[28] = Real(0); _b[29] = Real(0); _b[32] = Real(0); _b[33] = Real(0); _b[36] = Real(0); _b[37] = Real(0); _b[40] = Real(0); _b[41] = Real(0); _b[44] = Real(0); _b[45] = Real(0); _b[48] = Real(0); _b[49] = Real(0); _b[52] = Real(0); _b[53] = Real(0); _b[56] = Real(0); _b[57] = Real(0); _b[60] = Real(0); _b[61] = Real(0); _b[64] = Real(0); _b[65] = Real(0); _b[68] = Real(0); _b[69] = Real(0); _b[72] = Real(0); _b[73] = Real(0); _b[76] = Real(0); _b[77] = Real(0); break;
			default: break;
		}
		return _b;
	}
	template<> std::array<P2TetCGV, P2TetCGV::schemes[0]> P2TetCGV::split_impl<0>() const {
		auto _r_m0 = subdiv_0_3p3_1p3(degenerateZeroed_m0());
		auto _r_x0 = subdiv_0_3p1_1p1(x0);
		auto _r_x1 = subdiv_0_3p1_1p1(x1);
		auto _r_x2 = subdiv_0_3p1_1p1(x2);
		auto _r_x3 = subdiv_0_3p1_1p1(x3);
		return {
			P2TetCGV{*this, 0,
				_r_m0[0], 
				_r_x0[0], 
				_r_x1[0], 
				_r_x2[0], 
				_r_x3[0]
			},
			P2TetCGV{*this, 1,
				_r_m0[1], 
				_r_x0[1], 
				_r_x1[1], 
				_r_x2[1], 
				_r_x3[1]
			},
			P2TetCGV{*this, 2,
				_r_m0[2], 
				_r_x0[2], 
				_r_x1[2], 
				_r_x2[2], 
				_r_x3[2]
			},
			P2TetCGV{*this, 3,
				_r_m0[3], 
				_r_x0[3], 
				_r_x1[3], 
				_r_x2[3], 
				_r_x3[3]
			},
			P2TetCGV{*this, 4,
				_r_m0[4], 
				_r_x0[4], 
				_r_x1[4], 
				_r_x2[4], 
				_r_x3[4]
			},
			P2TetCGV{*this, 5,
				_r_m0[5], 
				_r_x0[5], 
				_r_x1[5], 
				_r_x2[5], 
				_r_x3[5]
			},
			P2TetCGV{*this, 6,
				_r_m0[6], 
				_r_x0[6], 
				_r_x1[6], 
				_r_x2[6], 
				_r_x3[6]
			},
			P2TetCGV{*this, 7,
				_r_m0[7], 
				_r_x0[7], 
				_r_x1[7], 
				_r_x2[7], 
				_r_x3[7]
			},
			P2TetCGV{*this, 8,
				_r_m0[8], 
				_r_x0[8], 
				_r_x1[8], 
				_r_x2[8], 
				_r_x3[8]
			},
			P2TetCGV{*this, 9,
				_r_m0[9], 
				_r_x0[9], 
				_r_x1[9], 
				_r_x2[9], 
				_r_x3[9]
			},
			P2TetCGV{*this, 10,
				_r_m0[10], 
				_r_x0[10], 
				_r_x1[10], 
				_r_x2[10], 
				_r_x3[10]
			},
			P2TetCGV{*this, 11,
				_r_m0[11], 
				_r_x0[11], 
				_r_x1[11], 
				_r_x2[11], 
				_r_x3[11]
			},
			P2TetCGV{*this, 12,
				_r_m0[12], 
				_r_x0[12], 
				_r_x1[12], 
				_r_x2[12], 
				_r_x3[12]
			},
			P2TetCGV{*this, 13,
				_r_m0[13], 
				_r_x0[13], 
				_r_x1[13], 
				_r_x2[13], 
				_r_x3[13]
			},
			P2TetCGV{*this, 14,
				_r_m0[14], 
				_r_x0[14], 
				_r_x1[14], 
				_r_x2[14], 
				_r_x3[14]
			},
			P2TetCGV{*this, 15,
				_r_m0[15], 
				_r_x0[15], 
				_r_x1[15], 
				_r_x2[15], 
				_r_x3[15]
			},
		};
	}
	template<> std::array<P2TetCGV, P2TetCGV::schemes[1]> P2TetCGV::split_impl<1>() const {
		auto _r_m0 = subdiv_1_3p3_1p3(degenerateZeroed_m0());
		auto _r_x0 = subdiv_1_3p1_1p1(x0);
		auto _r_x1 = subdiv_1_3p1_1p1(x1);
		auto _r_x2 = subdiv_1_3p1_1p1(x2);
		auto _r_x3 = subdiv_1_3p1_1p1(x3);
		return {
			P2TetCGV{*this, 16,
				_r_m0[0], 
				_r_x0[0], 
				_r_x1[0], 
				_r_x2[0], 
				_r_x3[0]
			},
			P2TetCGV{*this, 17,
				_r_m0[1], 
				_r_x0[1], 
				_r_x1[1], 
				_r_x2[1], 
				_r_x3[1]
			},
		};
	}
	std::ostream &operator<<(std::ostream &out, const P2TetCGV &s) {
		for (unsigned i=0; i<s.numVertices; ++i) {
			out << s.getVertex(i) << ' ';
		}
		return out;
	}
}
