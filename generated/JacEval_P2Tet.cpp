#include "JacEval_P2Tet.hpp"
namespace miso {
	Real JacEval_P2Tet(const RealVector<10> &px, const RealVector<10> &py, const RealVector<10> &pz, const Real x0, const Real x1, const Real x2) {
		#pragma region Temporaries
		const Real _t0 = 2*px[1];
		const Real _t1 = 4*x2;
		const Real _t2 = 2*px[3];
		const Real _t3 = -_t2*x1;
		const Real _t4 = 2*x2;
		const Real _t5 = 2*x1;
		const Real _t6 = 2*x0;
		const Real _t7 = 2*px[0];
		const Real _t8 = -_t7;
		const Real _t9 = 2*px[6];
		const Real _t10 = _t7*x0;
		const Real _t11 = _t7*x1;
		const Real _t12 = _t7*x2;
		const Real _t13 = _t10 + _t11 + _t12 + _t8 - _t9*x0;
		const Real _t14 = -_t0*x0 - _t0*x1 + _t0 - _t1*px[1] + _t13 + _t3 + _t4*px[2] + _t5*px[4] + _t6*px[7];
		const Real _t15 = 2*py[0];
		const Real _t16 = -_t15;
		const Real _t17 = 2*py[3];
		const Real _t18 = _t15*x0;
		const Real _t19 = _t15*x1;
		const Real _t20 = _t15*x2;
		const Real _t21 = 2*py[1];
		const Real _t22 = -_t21*x2;
		const Real _t23 = 4*x1;
		const Real _t24 = 2*py[6];
		const Real _t25 = -_t24*x0;
		const Real _t26 = _t16 - _t17*x0 - _t17*x2 + _t17 + _t18 + _t19 + _t20 + _t22 - _t23*py[3] + _t25 + _t4*py[4] + _t5*py[5] + _t6*py[8];
		const Real _t27 = 2*pz[6];
		const Real _t28 = 4*x0;
		const Real _t29 = 2*pz[3];
		const Real _t30 = -_t29*x1;
		const Real _t31 = 2*pz[0];
		const Real _t32 = -_t31;
		const Real _t33 = 2*pz[1];
		const Real _t34 = _t31*x0;
		const Real _t35 = _t31*x1;
		const Real _t36 = _t31*x2;
		const Real _t37 = _t32 - _t33*x2 + _t34 + _t35 + _t36;
		const Real _t38 = -_t27*x1 - _t27*x2 + _t27 - _t28*pz[6] + _t30 + _t37 + _t4*pz[7] + _t5*pz[8] + _t6*pz[9];
		const Real _t39 = -_t0*x2;
		const Real _t40 = _t13 - _t2*x0 - _t2*x2 + _t2 - _t23*px[3] + _t39 + _t4*px[4] + _t5*px[5] + _t6*px[8];
		const Real _t41 = _t16 - _t17*x1 + _t18 + _t19 + _t20;
		const Real _t42 = _t22 - _t24*x1 - _t24*x2 + _t24 - _t28*py[6] + _t4*py[7] + _t41 + _t5*py[8] + _t6*py[9];
		const Real _t43 = -_t27*x0;
		const Real _t44 = -_t1*pz[1] + _t30 + _t32 - _t33*x0 - _t33*x1 + _t33 + _t34 + _t35 + _t36 + _t4*pz[2] + _t43 + _t5*pz[4] + _t6*pz[7];
		const Real _t45 = _t10 + _t11 + _t12 - _t28*px[6] + _t3 + _t39 + _t4*px[7] + _t5*px[8] + _t6*px[9] + _t8 - _t9*x1 - _t9*x2 + _t9;
		const Real _t46 = -_t1*py[1] - _t21*x0 - _t21*x1 + _t21 + _t25 + _t4*py[2] + _t41 + _t5*py[4] + _t6*py[7];
		const Real _t47 = -_t23*pz[3] - _t29*x0 - _t29*x2 + _t29 + _t37 + _t4*pz[4] + _t43 + _t5*pz[5] + _t6*pz[8];
		#pragma endregion
		return -_t14*_t26*_t38 + _t14*_t42*_t47 + _t26*_t44*_t45 + _t38*_t40*_t46 - _t40*_t42*_t44 - _t45*_t46*_t47;
	}
}
