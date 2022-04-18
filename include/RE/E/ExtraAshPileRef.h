#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraAshPileRef : public BSExtraData
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_ExtraAshPileRef;
		SKYRIM_ADDR static auto VTABLE = VTABLE_ExtraAshPileRef;
		inline static auto      EXTRADATATYPE = ExtraDataType::kAshPileRef;

		ExtraAshPileRef();
		explicit ExtraAshPileRef(ObjectRefHandle a_ashPileRef);
		virtual ~ExtraAshPileRef() = default;  // 00

		// override (BSExtraData)
		virtual ExtraDataType GetType() const override;  // 01 - { return kAshPileRef; }

		// members
		ObjectRefHandle ashPileRef;  // 10
		std::uint32_t   pad14;       // 14
	};
	static_assert(sizeof(ExtraAshPileRef) == 0x18);
}
