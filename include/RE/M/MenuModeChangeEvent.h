#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	struct MenuModeChangeEvent
	{
		enum Mode : std::uint8_t
		{
			kHidden = 0,
			kDisplayed = 1
		};

		BSFixedString menu;  // 00
		Mode          mode;  // 08
	};
}
