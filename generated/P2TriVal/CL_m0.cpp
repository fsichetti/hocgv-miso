#include "../P2TriVal.hpp"
namespace miso {
	RealVector<6> P2TriVal::CL_m0(const RealVector<6> &px, const RealVector<6> &py) {
		#pragma region Temporaries
		const Real _t0 = 2*px[0];
		const Real _t1 = 2*px[1];
		const Real _t2 = 2*py[0];
		const Real _t3 = 2*py[3];
		const Real _t4 = 2*px[3];
		const Real _t5 = 2*py[1];
		const Real _t6 = -px[2];
		const Real _t7 = -py[4];
		const Real _t8 = _t7 + py[0];
		const Real _t9 = -py[2];
		const Real _t10 = -px[4];
		const Real _t11 = _t10 + px[0];
		const Real _t12 = -2*py[4];
		const Real _t13 = -2*px[4];
		const Real _t14 = -px[5];
		const Real _t15 = -py[5];
		const Real _t16 = _t10 + px[1] + px[3];
		const Real _t17 = _t7 + py[1] + py[3];
		#pragma endregion
		#pragma region Expressions
		return {
			-(-_t0 + _t1)*(-_t2 + _t3) + (-_t0 + _t4)*(-_t2 + _t5),
			-(-_t6 - px[0])*(-_t8 - py[1] + py[3]) + (-_t9 - py[0])*(-_t11 - px[1] + px[3]),
			(-_t1 - _t13)*(-_t5 + 2*py[2]) - (-_t1 + 2*px[2])*(-_t12 - _t5),
			(-_t14 - px[0])*(-_t8 + py[1] - py[3]) - (-_t15 - py[0])*(-_t11 + px[1] - px[3]),
			(-_t14 - _t16)*(-_t17 - _t9) - (-_t15 - _t17)*(-_t16 - _t6),
			(-_t12 - _t3)*(-_t4 + 2*px[5]) - (-_t13 - _t4)*(-_t3 + 2*py[5]),
		};
		#pragma endregion
	}
}
