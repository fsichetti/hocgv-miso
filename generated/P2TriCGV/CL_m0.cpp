#include "../P2TriCGV.hpp"
namespace miso {
	RealVector<18> P2TriCGV::CL_m0(const RealVector<6> &p0x, const RealVector<6> &p0y, const RealVector<6> &p1x, const RealVector<6> &p1y) {
		#pragma region Temporaries
		const Real _t0 = 2*p0x[0];
		const Real _t1 = 2*p0x[1];
		const Real _t2 = 2*p0y[0];
		const Real _t3 = 2*p0y[3];
		const Real _t4 = 2*p0x[3];
		const Real _t5 = 2*p0y[1];
		const Real _t6 = -p0x[1];
		const Real _t7 = -p1x[1];
		const Real _t8 = p0x[0] + p1x[0];
		const Real _t9 = -p0y[3];
		const Real _t10 = -p1y[3];
		const Real _t11 = p0y[0] + p1y[0];
		const Real _t12 = -p0x[3];
		const Real _t13 = -p1x[3];
		const Real _t14 = -p0y[1];
		const Real _t15 = -p1y[1];
		const Real _t16 = 2*p1x[0];
		const Real _t17 = 2*p1x[1];
		const Real _t18 = 2*p1y[0];
		const Real _t19 = 2*p1y[3];
		const Real _t20 = 2*p1x[3];
		const Real _t21 = 2*p1y[1];
		const Real _t22 = -p0x[2];
		const Real _t23 = -p0y[4];
		const Real _t24 = _t23 + p0y[1];
		const Real _t25 = -p0y[2];
		const Real _t26 = -p0x[4];
		const Real _t27 = _t26 + p0x[1];
		const Real _t28 = (0.5)*p0x[0] + (0.5)*p1x[0];
		const Real _t29 = -0.5*p0x[2] - 0.5*p1x[2];
		const Real _t30 = (0.5)*p0y[3];
		const Real _t31 = (0.5)*p1y[3];
		const Real _t32 = -0.5*p0y[4];
		const Real _t33 = -0.5*p1y[4];
		const Real _t34 = (0.5)*p0y[0] + (0.5)*p1y[0];
		const Real _t35 = _t32 + _t33 + _t34;
		const Real _t36 = (0.5)*p0y[1];
		const Real _t37 = (0.5)*p1y[1];
		const Real _t38 = _t36 + _t37;
		const Real _t39 = -0.5*p0y[2] - 0.5*p1y[2];
		const Real _t40 = (0.5)*p0x[3];
		const Real _t41 = (0.5)*p1x[3];
		const Real _t42 = -0.5*p0x[4];
		const Real _t43 = -0.5*p1x[4];
		const Real _t44 = _t28 + _t42 + _t43;
		const Real _t45 = (0.5)*p0x[1];
		const Real _t46 = (0.5)*p1x[1];
		const Real _t47 = _t45 + _t46;
		const Real _t48 = -p1x[2];
		const Real _t49 = -p1y[4];
		const Real _t50 = _t49 + p1y[1];
		const Real _t51 = -p1y[2];
		const Real _t52 = -p1x[4];
		const Real _t53 = _t52 + p1x[1];
		const Real _t54 = -2*p0y[4];
		const Real _t55 = -2*p0x[4];
		const Real _t56 = -2*p1y[4];
		const Real _t57 = -2*p1x[4];
		const Real _t58 = -p0x[5];
		const Real _t59 = _t23 + p0y[3];
		const Real _t60 = -p0y[5];
		const Real _t61 = _t26 + p0x[3];
		const Real _t62 = -0.5*p0x[5] - 0.5*p1x[5];
		const Real _t63 = _t30 + _t31;
		const Real _t64 = -0.5*p0y[5] - 0.5*p1y[5];
		const Real _t65 = _t40 + _t41;
		const Real _t66 = -p1x[5];
		const Real _t67 = _t49 + p1y[3];
		const Real _t68 = -p1y[5];
		const Real _t69 = _t52 + p1x[3];
		const Real _t70 = _t27 + p0x[3];
		const Real _t71 = _t24 + p0y[3];
		const Real _t72 = _t42 + _t43 + _t47 + _t65;
		const Real _t73 = _t32 + _t33 + _t38 + _t63;
		const Real _t74 = _t53 + p1x[3];
		const Real _t75 = _t50 + p1y[3];
		#pragma endregion
		#pragma region Expressions
		return {
			-(-_t0 + _t1)*(-_t2 + _t3) + (-_t0 + _t4)*(-_t2 + _t5),
			-(-_t10 - _t11 - _t9)*(-_t6 - _t7 - _t8) + (-_t11 - _t14 - _t15)*(-_t12 - _t13 - _t8),
			-(-_t16 + _t17)*(-_t18 + _t19) + (-_t16 + _t20)*(-_t18 + _t21),
			-(-_t22 - p0x[0])*(-_t24 - _t9 - p0y[0]) + (-_t25 - p0y[0])*(-_t12 - _t27 - p0x[0]),
			-(-_t28 - _t29)*(_t30 + _t31 - _t35 - _t38) + (-_t34 - _t39)*(_t40 + _t41 - _t44 - _t47),
			-(-_t48 - p1x[0])*(-_t10 - _t50 - p1y[0]) + (-_t51 - p1y[0])*(-_t13 - _t53 - p1x[0]),
			(-_t1 - _t55)*(-_t5 + 2*p0y[2]) - (-_t1 + 2*p0x[2])*(-_t5 - _t54),
			-(-_t24 - _t50)*(-_t22 - _t48 - p0x[1] - p1x[1]) + (-_t27 - _t53)*(-_t25 - _t51 - p0y[1] - p1y[1]),
			(-_t17 - _t57)*(-_t21 + 2*p1y[2]) - (-_t17 + 2*p1x[2])*(-_t21 - _t56),
			(-_t58 - p0x[0])*(-_t14 - _t59 - p0y[0]) - (-_t60 - p0y[0])*(-_t6 - _t61 - p0x[0]),
			(-_t28 - _t62)*(-_t35 + _t36 + _t37 - _t63) - (-_t34 - _t64)*(-_t44 + _t45 + _t46 - _t65),
			(-_t66 - p1x[0])*(-_t15 - _t67 - p1y[0]) - (-_t68 - p1y[0])*(-_t69 - _t7 - p1x[0]),
			-(-_t22 - _t70)*(-_t60 - _t71) + (-_t25 - _t71)*(-_t58 - _t70),
			-(-_t29 - _t72)*(-_t64 - _t73) + (-_t39 - _t73)*(-_t62 - _t72),
			-(-_t48 - _t74)*(-_t68 - _t75) + (-_t51 - _t75)*(-_t66 - _t74),
			(-_t3 - _t54)*(-_t4 + 2*p0x[5]) - (-_t3 + 2*p0y[5])*(-_t4 - _t55),
			(-_t59 - _t67)*(-_t58 - _t66 - p0x[3] - p1x[3]) - (-_t61 - _t69)*(-_t60 - _t68 - p0y[3] - p1y[3]),
			(-_t19 - _t56)*(-_t20 + 2*p1x[5]) - (-_t19 + 2*p1y[5])*(-_t20 - _t57),
		};
		#pragma endregion
	}
}
