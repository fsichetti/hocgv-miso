#include "../P2TetCGV.hpp"
namespace miso {
	RealVector<8> P2TetCGV::subdiv_0_3p1_1p1_6(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.5)*_b[2];
		const Real _t1 = (0.25)*_b[2] + (0.25)*_b[3];
		#pragma endregion
		#pragma region Expressions
		return {
			_t0 + (0.5)*_b[0],
			_t1 + (0.25)*_b[0] + (0.25)*_b[1],
			_b[2],
			_t0 + (0.5)*_b[3],
			_t0 + (0.5)*_b[4],
			_t1 + (0.25)*_b[4] + (0.25)*_b[5],
			_t0 + (0.5)*_b[6],
			_t1 + (0.25)*_b[6] + (0.25)*_b[7],
		};
		#pragma endregion
	}
}
