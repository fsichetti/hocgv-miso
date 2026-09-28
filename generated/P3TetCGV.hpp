#pragma once
#include "core/RealVector.hpp"
#include "core/SubdivHistory.hpp"

namespace miso {
	class P3TetCGV {
		public:
		static constexpr unsigned dimension = 4;
		static constexpr unsigned numVertices = 8;
		static constexpr unsigned numConstraints = 1;
		static constexpr bool hasObjective = true;
		unsigned scheme = 0;
		unsigned depth = 0;
		std::shared_ptr<const SubdivHistory> history;
		unsigned degenerateState = 0;

		P3TetCGV(
			const RealVector<20> &p0x,
			const RealVector<20> &p0y,
			const RealVector<20> &p0z,
			const RealVector<20> &p1x,
			const RealVector<20> &p1y,
			const RealVector<20> &p1z
		);

		P3TetCGV() = default;

		unsigned schemeSize() const {
			auto s = (scheme < schemes.size()) ? scheme : 0;
			return schemes.at(s);
		}

		const Real width() const {
			return std::max({
				x0.inclusion().width(),
				x1.inclusion().width(),
				x2.inclusion().width(),
				x3.inclusion().width()
			});
		}

		RealVector<dimension> getVertex(unsigned i) const {
			return {
				x0[i],
				x1[i],
				x2[i],
				x3[i]
			};
		}

		static constexpr std::array<unsigned, 3> schemes = {16, 2, 40};

		static constexpr unsigned numDegenerateStates = 89;
		static unsigned degenerateStateFromVertices(unsigned vertexMask, unsigned order = 1);
		static unsigned degenerateStateVertexMask(unsigned s);
		static unsigned degenerateStateOrder(unsigned s);
		static unsigned degenerateTransition(unsigned s, unsigned q);

		RealInterval inclusion(unsigned i) const;
		RealVector<numVertices> sample(unsigned i) const;
		template<typename F> void split(unsigned scheme, F &&f) const {
			if (degenerateState != 0) scheme = 2;
			if (scheme == 2) { for (auto &&_c : split_impl<2>()) f(std::move(_c)); }
			else if (scheme == 1) { for (auto &&_c : split_impl<1>()) f(std::move(_c)); }
			else { for (auto &&_c : split_impl<0>()) f(std::move(_c)); }
		}
		void inherit(const P3TetCGV &parent, unsigned q);
		friend std::ostream &operator<<(std::ostream &out, const P3TetCGV &s);

		private:

		RealVector<336> m0;
		RealVector<8> x0;
		RealVector<8> x1;
		RealVector<8> x2;
		RealVector<8> x3;

		P3TetCGV(const P3TetCGV &parent, unsigned q,
			const RealVector<336> &m0,
			const RealVector<8> &x0,
			const RealVector<8> &x1,
			const RealVector<8> &x2,
			const RealVector<8> &x3
		);

		static RealVector<336> CL_m0(const RealVector<20> &p0x, const RealVector<20> &p0y, const RealVector<20> &p0z, const RealVector<20> &p1x, const RealVector<20> &p1y, const RealVector<20> &p1z);
		static RealVector<336> LB_3p6_1p3(const RealVector<336> &_l);
		static RealVector<336> subdiv_0_3p6_1p3_0(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_1(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_2(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_3(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_4(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_5(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_6(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_7(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_8(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_9(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_10(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_11(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_12(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_13(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_14(const RealVector<336> &_b);
		static RealVector<336> subdiv_0_3p6_1p3_15(const RealVector<336> &_b);
		static RealVector<336> subdiv_1_3p6_1p3_0(const RealVector<336> &_b);
		static RealVector<336> subdiv_1_3p6_1p3_1(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_0(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_1(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_2(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_3(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_4(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_5(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_6(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_7(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_8(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_9(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_10(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_11(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_12(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_13(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_14(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_15(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_16(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_17(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_18(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_19(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_20(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_21(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_22(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_23(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_24(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_25(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_26(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_27(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_28(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_29(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_30(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_31(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_32(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_33(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_34(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_35(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_36(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_37(const RealVector<336> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_38(const RealVector<336> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_0(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_1(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_2(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_3(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_4(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_5(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_6(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_7(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_8(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_9(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_10(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_11(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_12(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_13(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_14(const RealVector<8> &_b);
		static RealVector<8> subdiv_0_3p1_1p1_15(const RealVector<8> &_b);
		static RealVector<8> subdiv_1_3p1_1p1_0(const RealVector<8> &_b);
		static RealVector<8> subdiv_1_3p1_1p1_1(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_0(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_1(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_2(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_3(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_4(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_5(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_6(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_7(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_8(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_9(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_10(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_11(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_12(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_13(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_14(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_15(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_16(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_17(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_18(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_19(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_20(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_21(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_22(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_23(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_24(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_25(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_26(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_27(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_28(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_29(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_30(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_31(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_32(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_33(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_34(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_35(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_36(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_37(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_38(const RealVector<8> &_b);
		static RealVector<8> subdiv_2_3p1_1p1_39(const RealVector<8> &_b);
		static RealVector<336> subdiv_2_3p6_1p3_39(const RealVector<336> &_b);
		RealVector<336> degenerateZeroed_m0() const;
		template<unsigned SI=0> std::array<P3TetCGV, schemes[SI]> split_impl() const;
	};

	template<> std::array<P3TetCGV, P3TetCGV::schemes[0]> P3TetCGV::split_impl<0>() const;
	template<> std::array<P3TetCGV, P3TetCGV::schemes[1]> P3TetCGV::split_impl<1>() const;
	template<> std::array<P3TetCGV, P3TetCGV::schemes[2]> P3TetCGV::split_impl<2>() const;
}
