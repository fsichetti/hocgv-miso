#include "../P3TetCGV.hpp"
namespace miso {
	RealVector<8> P3TetCGV::subdiv_2_3p1_1p1_0(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.5)*_b[0];
		const Real _t1 = (0.25)*_b[6];
		const Real _t2 = _t0 + _t1;
		const Real _t3 = (0.25)*_b[0] + (0.25)*_b[1];
		const Real _t4 = _t3 + (0.125)*_b[6] + (0.125)*_b[7];
		#pragma endregion
		#pragma region Expressions
		return {
			_b[0],
			_t0 + (0.5)*_b[1],
			_t2 + (0.25)*_b[2],
			_t4 + (0.125)*_b[2] + (0.125)*_b[3],
			_t2 + (0.25)*_b[4],
			_t4 + (0.125)*_b[4] + (0.125)*_b[5],
			_t0 + (0.5)*_b[6],
			_t1 + _t3 + (0.25)*_b[7],
		};
		#pragma endregion
	}
}
