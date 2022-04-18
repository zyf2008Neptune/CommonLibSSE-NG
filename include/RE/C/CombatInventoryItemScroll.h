#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemScroll : public CombatInventoryItemMagic
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_CombatInventoryItemScroll;
		SKYRIM_ADDR static auto VTABLE = VTABLE_CombatInventoryItemScroll;

		~CombatInventoryItemScroll() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE GetType() override;                                  // 09 - { return 8; }
		bool CheckBusy(CombatController* a_controller) override;  // 0E
	};
	static_assert(sizeof(CombatInventoryItemScroll) == 0x50);
}
