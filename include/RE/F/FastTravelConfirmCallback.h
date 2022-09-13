#pragma once

#include "RE/M/MapMenu.h"

namespace RE
{
	class FastTravelConfirmCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___FastTravelConfirmCallback;
		inline static constexpr auto VTABLE = VTABLE___FastTravelConfirmCallback;

		virtual ~FastTravelConfirmCallback();  // 00

		//add
		virtual bool Run(bool a_arg1);  //01

		//members
		std::uint64_t refCount;  // 08
		MapMenu*      mapMenu;   // 10
		std::uint32_t unk18;     // 18
		std::uint32_t unk1C;     // 1C
#ifdef SKYRIMVR
		RE::NiPoint3  coords;  // 20
		std::uint16_t unk2c;   // 2c
#endif
	};
	static_assert(sizeof(FastTravelConfirmCallback) ==
#ifndef SKYRIMVR
				  0x20
#else
				  0x30
#endif
	);

}
