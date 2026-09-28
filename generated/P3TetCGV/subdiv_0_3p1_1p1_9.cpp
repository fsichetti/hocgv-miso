#include "../P3TetCGV.hpp"
namespace miso {
	RealVector<8> P3TetCGV::subdiv_0_3p1_1p1_9(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.25)*_b[6] + (0.25)*_b[7];
		const Real _t1 = (0.25)*_b[0] + (0.25)*_b[1];
		const Real _t2 = (0.5)*_b[1];
		const Real _t3 = (0.5)*_b[7];
		const Real _t4 = (0.25)*_b[2] + (0.25)*_b[3];
		const Real _t5 = (0.5)*_b[3];
		#pragma endregion
		#pragma region Expressions
		return {
			_t0 + _t1,
			_t2 + _t3,
			_t0 + _t4,
			_t3 + _t5,
			_t1 + _t4,
			_t2 + _t5,
			_t1 + (0.25)*_b[4] + (0.25)*_b[5],
			_t2 + (0.5)*_b[5],
		};
		#pragma endregion
	}
}
