#pragma once

#include "RE/B/BSGeometry.h"

namespace RE
{
	class NiParticlesData;

	class NiParticles : public BSGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiParticles;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiParticles;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                           \
	NiPointer<NiParticlesData> particleData; /*  158*/ \
	std::uint64_t              unk160;       /*  160*/

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);
		~NiParticles() override;  // 00

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiParticles*  AsParticlesGeom() override;                         // 10
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { BSGeometry::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return BSGeometry::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return BSGeometry::IsEqual(); }

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x158, 0x198);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x158, 0x198);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(NiParticles) == 0x168);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(NiParticles) == 0x1B0);
#else
	static_assert(sizeof(NiParticles) == 0x110);
#endif
}
#undef RUNTIME_DATA_CONTENT
