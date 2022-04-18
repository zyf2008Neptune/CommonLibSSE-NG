#pragma once

namespace RE
{
	class hkBaseObject
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_hkBaseObject;

		virtual ~hkBaseObject() = default;  // 00
	};
	static_assert(sizeof(hkBaseObject) == 0x8);
}
