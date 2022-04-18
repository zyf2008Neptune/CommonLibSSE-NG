#pragma once

#include "RE/I/IUIMessageData.h"

namespace RE
{
	class GFxEvent;

	class BSUIScaleformData : public IUIMessageData
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_BSUIScaleformData;

		~BSUIScaleformData() override;  // 00

		// members
		GFxEvent* scaleformEvent;  // 10
	};
	static_assert(sizeof(BSUIScaleformData) == 0x18);
}
