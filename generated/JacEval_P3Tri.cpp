#include "JacEval_P3Tri.hpp"
namespace miso {
	Real JacEval_P3Tri(const RealVector<10> &px, const RealVector<10> &py, const Real x0, const Real x1) {
		#pragma region Temporaries
		const Real _t0 = 3*px[1];
		const Real _t1 = 12*x1;
		const Real _t2 = _t1*px[1];
		const Real _t3 = pown(x1, 2);
		const Real _t4 = 9*_t3;
		const Real _t5 = 6*x0;
		const Real _t6 = px[4]*x0;
		const Real _t7 = pown(x0, 2);
		const Real _t8 = 6*_t7;
		const Real _t9 = 3*_t7;
		const Real _t10 = 3*_t3;
		const Real _t11 = 6*x1;
		const Real _t12 = _t11*px[2];
		const Real _t13 = _t11*x0;
		const Real _t14 = 3*px[0];
		const Real _t15 = _t11*px[0];
		const Real _t16 = _t1*x0;
		const Real _t17 = -_t14*_t3 - _t14*_t7 - _t14 - _t15*x0 + _t15 - _t16*px[5] + _t5*px[0];
		const Real _t18 = 3*py[4];
		const Real _t19 = py[4]*x0;
		const Real _t20 = 9*_t7;
		const Real _t21 = _t11*py[1];
		const Real _t22 = 6*_t3;
		const Real _t23 = 3*py[0];
		const Real _t24 = _t11*py[0];
		const Real _t25 = -_t16*py[5] - _t23*_t3 - _t23*_t7 - _t23 - _t24*x0 + _t24 + _t5*py[0];
		const Real _t26 = 3*px[4];
		const Real _t27 = 12*_t6;
		const Real _t28 = _t11*px[1];
		const Real _t29 = 3*py[1];
		const Real _t30 = _t1*py[1];
		const Real _t31 = _t11*py[2];
		#pragma endregion
		return -(_t0*_t7 + _t0 + _t10*px[3] + _t11*_t6 - _t12*x0 + _t12 + _t13*px[6] + _t17 + _t2*x0 - _t2 + _t4*px[1] - _t4*px[2] - _t5*px[1] + _t5*px[5] - 6*_t6 + _t8*px[4] - _t8*px[5] - _t9*px[7] + _t9*px[8])*(_t1*_t19 - _t10*py[2] + _t10*py[6] - _t11*py[4] + _t11*py[5] - _t13*py[7] + _t13*py[8] + _t18*_t3 + _t18 - 12*_t19 + _t20*py[4] - _t20*py[7] + _t21*x0 - _t21 + _t22*py[1] - _t22*py[5] + _t25 + _t5*py[7] + _t9*py[9]) + (-_t10*px[2] + _t10*px[6] - _t11*px[4] + _t11*px[5] - _t13*px[7] + _t13*px[8] + _t17 + _t20*px[4] - _t20*px[7] + _t22*px[1] - _t22*px[5] + _t26*_t3 + _t26 + _t27*x1 - _t27 + _t28*x0 - _t28 + _t5*px[7] + _t9*px[9])*(_t10*py[3] + _t11*_t19 + _t13*py[6] + _t25 + _t29*_t7 + _t29 + _t30*x0 - _t30 - _t31*x0 + _t31 + _t4*py[1] - _t4*py[2] - _t5*py[1] - _t5*py[4] + _t5*py[5] + _t8*py[4] - _t8*py[5] - _t9*py[7] + _t9*py[8]);
	}
}
