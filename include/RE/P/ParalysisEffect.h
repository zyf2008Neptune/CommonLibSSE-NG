#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class ParalysisEffect : public ValueModifierEffect
	{
	public:
		inline static auto RTTI = RTTI_ParalysisEffect;
		inline static auto VTABLE = VTABLE_ParalysisEffect;

		// override (ValueModifierEffect)
		void Unk_04(void) override;  // 04

		~ParalysisEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15
	};
	static_assert(sizeof(ParalysisEffect) == 0x98);
}
