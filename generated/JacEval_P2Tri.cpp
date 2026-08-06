#include "JacEval_P2Tri.hpp"
namespace miso {
	Real JacEval_P2Tri(const RealVector<6> &px, const RealVector<6> &py, const Real x0, const Real x1) {
		#pragma region Temporaries
		const Real _t0 = 2*px[1];
		const Real _t1 = 4*x1;
		const Real _t2 = 2*px[3];
		const Real _t3 = 2*x1;
		const Real _t4 = 2*x0;
		const Real _t5 = 2*px[0];
		const Real _t6 = _t5*x0 + _t5*x1 - _t5;
		const Real _t7 = 2*py[3];
		const Real _t8 = 4*x0;
		const Real _t9 = 2*py[1];
		const Real _t10 = 2*py[0];
		const Real _t11 = _t10*x0 + _t10*x1 - _t10;
		#pragma endregion
		return -(_t11 + _t3*py[4] + _t4*py[5] - _t7*x1 + _t7 - _t8*py[3] - _t9*x1)*(-_t0*x0 + _t0 - _t1*px[1] - _t2*x0 + _t3*px[2] + _t4*px[4] + _t6) + (-_t0*x1 - _t2*x1 + _t2 + _t3*px[4] + _t4*px[5] + _t6 - _t8*px[3])*(-_t1*py[1] + _t11 + _t3*py[2] + _t4*py[4] - _t7*x0 - _t9*x0 + _t9);
	}
}
