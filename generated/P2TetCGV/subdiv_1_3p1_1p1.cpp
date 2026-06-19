#include "../P2TetCGV.hpp"
namespace miso {
	std::array<RealVector<8>, 2> P2TetCGV::subdiv_1_3p1_1p1(const RealVector<8> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.5)*_b[6] + (0.5)*_b[7];
		const Real _t1 = (0.5)*_b[0] + (0.5)*_b[1];
		const Real _t2 = (0.5)*_b[2] + (0.5)*_b[3];
		const Real _t3 = (0.5)*_b[4] + (0.5)*_b[5];
		#pragma endregion
		#pragma region Expressions
		return {{
			{
				_b[6],
				_t0,
				_b[0],
				_t1,
				_b[2],
				_t2,
				_b[4],
				_t3,
			},
			{
				_t0,
				_b[7],
				_t1,
				_b[1],
				_t2,
				_b[3],
				_t3,
				_b[5],
			},
		}};
		#pragma endregion
	}
}
