#include "../P3TriVal.hpp"
namespace miso {
	RealVector<15> P3TriVal::CL_m0(const RealVector<10> &px, const RealVector<10> &py) {
		#pragma region Temporaries
		const Real _t0 = 3*px[0];
		const Real _t1 = 3*py[0];
		const Real _t2 = (1.6875)*px[0];
		const Real _t3 = -_t2;
		const Real _t4 = (0.5625)*px[1];
		const Real _t5 = (0.1875)*px[3];
		const Real _t6 = (1.6875)*py[0];
		const Real _t7 = (1.125)*py[5];
		const Real _t8 = -_t7;
		const Real _t9 = _t8 + (1.125)*py[1];
		const Real _t10 = (0.1875)*py[2];
		const Real _t11 = _t10 - 0.1875*py[6];
		const Real _t12 = -_t6;
		const Real _t13 = (0.5625)*py[1];
		const Real _t14 = (0.1875)*py[3];
		const Real _t15 = (1.125)*px[5];
		const Real _t16 = -_t15;
		const Real _t17 = _t16 + (1.125)*px[1];
		const Real _t18 = (0.1875)*px[2];
		const Real _t19 = _t18 - 0.1875*px[6];
		const Real _t20 = (0.75)*px[0];
		const Real _t21 = (0.75)*px[1];
		const Real _t22 = (0.75)*px[2];
		const Real _t23 = -0.75*px[3];
		const Real _t24 = (0.75)*py[4];
		const Real _t25 = -_t24;
		const Real _t26 = (0.75)*py[0];
		const Real _t27 = (1.5)*py[5];
		const Real _t28 = _t26 - _t27;
		const Real _t29 = -0.75*py[6];
		const Real _t30 = (0.75)*py[2];
		const Real _t31 = _t29 + _t30;
		const Real _t32 = (0.75)*py[1];
		const Real _t33 = -0.75*py[3];
		const Real _t34 = (0.75)*px[4];
		const Real _t35 = -_t34;
		const Real _t36 = (1.5)*px[5];
		const Real _t37 = _t20 - _t36;
		const Real _t38 = -0.75*px[6];
		const Real _t39 = _t22 + _t38;
		const Real _t40 = (0.1875)*px[0];
		const Real _t41 = (0.5625)*px[2];
		const Real _t42 = -1.6875*px[3];
		const Real _t43 = (0.1875)*py[0];
		const Real _t44 = (0.1875)*py[4];
		const Real _t45 = (1.6875)*py[2];
		const Real _t46 = _t45 - 1.6875*py[6];
		const Real _t47 = (0.5625)*py[2];
		const Real _t48 = -1.6875*py[3];
		const Real _t49 = (0.1875)*px[4];
		const Real _t50 = (1.6875)*px[2];
		const Real _t51 = _t50 - 1.6875*px[6];
		const Real _t52 = 3*px[2];
		const Real _t53 = 3*py[2];
		const Real _t54 = (0.5625)*px[4];
		const Real _t55 = (0.1875)*px[9];
		const Real _t56 = (0.1875)*py[7];
		const Real _t57 = _t56 - 0.1875*py[8];
		const Real _t58 = _t8 + (1.125)*py[4];
		const Real _t59 = (0.5625)*py[4];
		const Real _t60 = (0.1875)*py[9];
		const Real _t61 = (0.1875)*px[7];
		const Real _t62 = _t61 - 0.1875*px[8];
		const Real _t63 = _t16 + (1.125)*px[4];
		const Real _t64 = (0.5625)*px[7];
		const Real _t65 = -_t21;
		const Real _t66 = -_t18;
		const Real _t67 = (0.375)*px[5];
		const Real _t68 = -_t20 + _t67;
		const Real _t69 = -_t56;
		const Real _t70 = (0.375)*py[5];
		const Real _t71 = -_t26 + _t70;
		const Real _t72 = -_t61;
		const Real _t73 = (0.5625)*py[7];
		const Real _t74 = -_t32;
		const Real _t75 = -_t10;
		const Real _t76 = -0.1875*px[9];
		const Real _t77 = -0.75*px[8];
		const Real _t78 = _t40 + _t77;
		const Real _t79 = _t29 + _t43;
		const Real _t80 = _t38 + _t40;
		const Real _t81 = -0.1875*py[9];
		const Real _t82 = -0.75*py[8];
		const Real _t83 = _t43 + _t82;
		const Real _t84 = _t15 - 1.125*px[6];
		const Real _t85 = _t7 - 1.125*py[8];
		const Real _t86 = _t15 - 1.125*px[8];
		const Real _t87 = _t7 - 1.125*py[6];
		const Real _t88 = (0.75)*px[7];
		const Real _t89 = -0.75*px[9];
		const Real _t90 = (0.75)*py[7];
		const Real _t91 = _t82 + _t90;
		const Real _t92 = -0.75*py[9];
		const Real _t93 = _t77 + _t88;
		const Real _t94 = -0.1875*py[3];
		const Real _t95 = (0.1875)*py[1];
		const Real _t96 = -0.1875*px[3];
		const Real _t97 = (0.1875)*px[1];
		const Real _t98 = -1.6875*px[9];
		const Real _t99 = (1.6875)*py[7];
		const Real _t100 = _t99 - 1.6875*py[8];
		const Real _t101 = -1.6875*py[9];
		const Real _t102 = (1.6875)*px[7];
		const Real _t103 = _t102 - 1.6875*px[8];
		const Real _t104 = 3*px[7];
		const Real _t105 = 3*py[7];
		#pragma endregion
		#pragma region Expressions
		return {
			-(-_t0 + 3*px[1])*(-_t1 + 3*py[4]) + (-_t0 + 3*px[4])*(-_t1 + 3*py[1]),
			-(-_t11 - _t6 - _t9 + (1.6875)*py[4])*(_t3 + _t4 + _t5 + (0.9375)*px[2]) + (-_t17 - _t19 - _t2 + (1.6875)*px[4])*(_t12 + _t13 + _t14 + (0.9375)*py[2]),
			-(-_t20 - _t21 + _t22 - _t23)*(-_t25 - _t28 - _t31 - 1.5*py[1]) + (-_t26 + _t30 - _t32 - _t33)*(-_t35 - _t37 - _t39 - 1.5*px[1]),
			(-_t17 - _t40 + _t49 - _t51)*(-_t43 - _t47 - _t48 - 0.9375*py[1]) - (-_t40 - _t41 - _t42 - 0.9375*px[1])*(-_t43 + _t44 - _t46 - _t9),
			-(-_t52 + 3*px[3])*(-_t53 + 3*py[6]) + (-_t52 + 3*px[6])*(-_t53 + 3*py[3]),
			-(-_t2 - _t62 - _t63 + (1.6875)*px[1])*(_t12 + _t59 + _t60 + (0.9375)*py[7]) + (-_t57 - _t58 - _t6 + (1.6875)*py[1])*(_t3 + _t54 + _t55 + (0.9375)*px[7]),
			(_t14 + _t25 + _t47 + _t69 + _t71 + (0.375)*py[6] + (0.1875)*py[8])*(_t55 + _t64 + _t65 + _t66 + _t68 + (0.1875)*px[6] + (0.375)*px[8]) - (_t35 + _t41 + _t5 + _t68 + _t72 + (0.375)*px[6] + (0.1875)*px[8])*(_t60 + _t71 + _t73 + _t74 + _t75 + (0.1875)*py[6] + (0.375)*py[8]),
			(-_t13 - _t33 - _t57 - _t70 - _t79 - 0.375*py[4])*(-_t21 - _t39 - _t49 - _t72 - _t76 - _t78) - (-_t23 - _t4 - _t62 - _t67 - _t80 - 0.375*px[4])*(-_t31 - _t32 - _t44 - _t69 - _t81 - _t83),
			-(-_t42 - _t50 - _t62 - _t84)*(-_t46 - _t56 - _t81 - _t85) + (-_t45 - _t48 - _t57 - _t87)*(-_t51 - _t61 - _t76 - _t86),
			(-_t20 - _t34 + _t88 - _t89)*(-_t28 - _t74 - _t91 - 1.5*py[4]) - (-_t24 - _t26 + _t90 - _t92)*(-_t37 - _t65 - _t93 - 1.5*px[4]),
			-(-_t11 - _t59 - _t70 - _t83 - _t92 - 0.375*py[1])*(-_t34 - _t66 - _t80 - _t93 - _t96 - _t97) + (-_t19 - _t54 - _t67 - _t78 - _t89 - 0.375*px[1])*(-_t24 - _t75 - _t79 - _t91 - _t94 - _t95),
			-(-_t22 - _t23 - _t36 - _t93 + (1.5)*px[6])*(-_t27 - _t31 - _t90 - _t92 + (1.5)*py[8]) + (-_t27 - _t30 - _t33 - _t91 + (1.5)*py[6])*(-_t36 - _t39 - _t88 - _t89 + (1.5)*px[8]),
			(-_t100 - _t43 - _t58 + _t95)*(-_t40 - _t64 - _t98 - 0.9375*px[4]) - (-_t101 - _t43 - _t73 - 0.9375*py[4])*(-_t103 - _t40 - _t63 + _t97),
			(-_t10 - _t100 - _t87 - _t94)*(-_t102 - _t19 - _t86 - _t98) - (-_t101 - _t11 - _t85 - _t99)*(-_t103 - _t18 - _t84 - _t96),
			-(-_t104 + 3*px[8])*(-_t105 + 3*py[9]) + (-_t104 + 3*px[9])*(-_t105 + 3*py[8]),
		};
		#pragma endregion
	}
}
