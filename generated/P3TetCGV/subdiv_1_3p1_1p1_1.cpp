#include "../P3TetCGV.hpp"
namespace miso {
	RealVector<8> P3TetCGV::subdiv_1_3p1_1p1_1(const RealVector<8> &_b) {
		#pragma region Expressions
		return {
			(0.5)*_b[0] + (0.5)*_b[1],
			_b[1],
			(0.5)*_b[2] + (0.5)*_b[3],
			_b[3],
			(0.5)*_b[4] + (0.5)*_b[5],
			_b[5],
			(0.5)*_b[6] + (0.5)*_b[7],
			_b[7],
		};
		#pragma endregion
	}
}
