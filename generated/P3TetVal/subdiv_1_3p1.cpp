#include "../P3TetVal.hpp"
namespace miso {
	std::array<RealVector<4>, 20> P3TetVal::subdiv_1_3p1(const RealVector<4> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.25)*_b[1];
		const Real _t1 = (0.5)*_b[0];
		const Real _t2 = (0.25)*_b[3];
		const Real _t3 = _t1 + _t2;
		const Real _t4 = _t0 + _t3;
		const Real _t5 = (0.25)*_b[2];
		const Real _t6 = _t3 + _t5;
		const Real _t7 = (0.5)*_b[3];
		const Real _t8 = _t1 + _t7;
		const Real _t9 = _t0 + _t5;
		const Real _t10 = _t1 + _t9;
		const Real _t11 = (0.5)*_b[2];
		const Real _t12 = _t1 + _t11;
		const Real _t13 = (0.5)*_b[1];
		const Real _t14 = _t1 + _t13;
		const Real _t15 = (0.25)*_b[0];
		const Real _t16 = _t15 + _t7;
		const Real _t17 = _t0 + _t16;
		const Real _t18 = _t16 + _t5;
		const Real _t19 = _t7 + _t9;
		const Real _t20 = _t11 + _t7;
		const Real _t21 = _t13 + _t7;
		const Real _t22 = _t11 + _t15;
		const Real _t23 = _t0 + _t22;
		const Real _t24 = _t2 + _t22;
		const Real _t25 = _t0 + _t11 + _t2;
		const Real _t26 = _t11 + _t13;
		const Real _t27 = _t13 + _t15;
		const Real _t28 = _t27 + _t5;
		const Real _t29 = _t2 + _t27;
		const Real _t30 = _t13 + _t2 + _t5;
		#pragma endregion
		#pragma region Expressions
		return {{
			{
				_b[0],
				_t4,
				_t6,
				_t8,
			},
			{
				_b[0],
				_t10,
				_t12,
				_t6,
			},
			{
				_b[0],
				_t14,
				_t10,
				_t4,
			},
			{
				_b[0],
				_t6,
				_t4,
				_t10,
			},
			{
				_b[3],
				_t17,
				_t18,
				_t8,
			},
			{
				_b[3],
				_t19,
				_t20,
				_t18,
			},
			{
				_b[3],
				_t21,
				_t19,
				_t17,
			},
			{
				_b[3],
				_t18,
				_t17,
				_t19,
			},
			{
				_b[2],
				_t23,
				_t24,
				_t12,
			},
			{
				_b[2],
				_t25,
				_t20,
				_t24,
			},
			{
				_b[2],
				_t26,
				_t25,
				_t23,
			},
			{
				_b[2],
				_t24,
				_t23,
				_t25,
			},
			{
				_b[1],
				_t28,
				_t29,
				_t14,
			},
			{
				_b[1],
				_t30,
				_t21,
				_t29,
			},
			{
				_b[1],
				_t26,
				_t30,
				_t28,
			},
			{
				_b[1],
				_t29,
				_t28,
				_t30,
			},
			{
				_t8,
				_t21,
				_t14,
				_t12,
			},
			{
				_t8,
				_t21,
				_t20,
				_t12,
			},
			{
				_t12,
				_t26,
				_t21,
				_t14,
			},
			{
				_t12,
				_t26,
				_t21,
				_t20,
			},
		}};
		#pragma endregion
	}
}
