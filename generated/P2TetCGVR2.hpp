#pragma once
#include "core/RealVector.hpp"
#include "core/SubdivHistory.hpp"

namespace miso {
	class P2TetCGVR2 {
		public:
		static constexpr unsigned dimension = 4;
		static constexpr unsigned numVertices = 8;
		static constexpr unsigned numConstraints = 1;
		static constexpr bool hasObjective = true;
		unsigned scheme = 0;
		unsigned depth = 0;
		std::shared_ptr<const SubdivHistory> history;

		P2TetCGVR2(
			const RealVector<10> &p0x,
			const RealVector<10> &p0y,
			const RealVector<10> &p0z,
			const RealVector<10> &p1x,
			const RealVector<10> &p1y,
			const RealVector<10> &p1z
		);

		P2TetCGVR2() = default;

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

		static constexpr std::array<unsigned, 2> schemes = {16, 2};

		RealInterval inclusion(unsigned i) const;
		RealVector<numVertices> sample(unsigned i) const;
		template<typename F> void split(unsigned scheme, F &&f) const {
			if (scheme == 1) { for (auto &&_c : split_impl<1>()) f(std::move(_c)); }
			else { for (auto &&_c : split_impl<0>()) f(std::move(_c)); }
		}
		void inherit(const P2TetCGVR2 &parent, unsigned q);
		friend std::ostream &operator<<(std::ostream &out, const P2TetCGVR2 &s);

		private:

		RealVector<80> m0;
		RealVector<80> m1;
		RealVector<8> x0;
		RealVector<8> x1;
		RealVector<8> x2;
		RealVector<8> x3;

		P2TetCGVR2(const P2TetCGVR2 &parent, unsigned q,
			const RealVector<80> &m0,
			const RealVector<80> &m1,
			const RealVector<8> &x0,
			const RealVector<8> &x1,
			const RealVector<8> &x2,
			const RealVector<8> &x3
		);

		static RealVector<80> CB_m0();
		static RealVector<80> CL_m1(const RealVector<10> &p0x, const RealVector<10> &p0y, const RealVector<10> &p0z, const RealVector<10> &p1x, const RealVector<10> &p1y, const RealVector<10> &p1z);
		static RealVector<80> LB_3p3_1p3(const RealVector<80> &_l);
		static std::array<RealVector<8>, 16> subdiv_0_3p1_1p1(const RealVector<8> &_b);
		static std::array<RealVector<8>, 2> subdiv_1_3p1_1p1(const RealVector<8> &_b);
		static std::array<RealVector<80>, 16> subdiv_0_3p3_1p3(const RealVector<80> &_b);
		static std::array<RealVector<80>, 2> subdiv_1_3p3_1p3(const RealVector<80> &_b);
		template<unsigned SI=0> std::array<P2TetCGVR2, schemes[SI]> split_impl() const;
	};

	template<> std::array<P2TetCGVR2, P2TetCGVR2::schemes[0]> P2TetCGVR2::split_impl<0>() const;
	template<> std::array<P2TetCGVR2, P2TetCGVR2::schemes[1]> P2TetCGVR2::split_impl<1>() const;
}
