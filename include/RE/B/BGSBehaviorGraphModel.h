#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class BGSBehaviorGraphModel : TESModel
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_BGSBehaviorGraphModel;

		~BGSBehaviorGraphModel() override;  // 00

		// override (TESModel)
		void SetModel(const char* a_model) override;  // 05
	};
	static_assert(sizeof(BGSBehaviorGraphModel) == 0x28);
}
