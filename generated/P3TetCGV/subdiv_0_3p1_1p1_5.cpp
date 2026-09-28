#include "../P3TetCGV.hpp"
namespace miso {
	RealVector<8> P3TetCGV::subdiv_0_3p1_1p1_5(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.25)*_b[4] + (0.25)*_b[5];
		const Real _t1 = (0.5)*_b[5];
		#pragma endregion
		#pragma region Expressions
		return {
			_t0 + (0.25)*_b[0] + (0.25)*_b[1],
			_t1 + (0.5)*_b[1],
			_t0 + (0.25)*_b[2] + (0.25)*_b[3],
			_t1 + (0.5)*_b[3],
			_t1 + (0.5)*_b[4],
			_b[5],
			_t0 + (0.25)*_b[6] + (0.25)*_b[7],
			_t1 + (0.5)*_b[7],
		};
		#pragma endregion
	}
}
