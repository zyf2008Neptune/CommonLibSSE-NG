#pragma once

#include "RE/T/TESModel.h"

namespace RE
{
	class TESModelRDT : public TESModel
	{
	public:
		inline static auto RTTI = RTTI_TESModelRDT;

		~TESModelRDT() override;  // 00
	};
	static_assert(sizeof(TESModelRDT) == 0x28);
}
