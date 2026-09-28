#include "../P3TetCGV.hpp"
namespace miso {
	RealVector<8> P3TetCGV::subdiv_2_3p1_1p1_15(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.5)*_b[7];
		const Real _t1 = (0.25)*_b[6];
		const Real _t2 = (0.25)*_b[7];
		const Real _t3 = _t1 + _t2 + (0.125)*_b[0] + (0.125)*_b[1];
		const Real _t4 = (0.125)*_b[4] + (0.125)*_b[5];
		const Real _t5 = (0.25)*_b[5];
		const Real _t6 = _t0 + (0.25)*_b[1];
		const Real _t7 = (0.125)*_b[2] + (0.125)*_b[3];
		const Real _t8 = (0.25)*_b[3];
		#pragma endregion
		#pragma region Expressions
		return {
			_t0 + (0.5)*_b[6],
			_b[7],
			_t3 + _t4,
			_t5 + _t6,
			_t3 + _t7,
			_t6 + _t8,
			_t1 + _t2 + _t4 + _t7,
			_t0 + _t5 + _t8,
		};
		#pragma endregion
	}
}
