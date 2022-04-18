#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemPotion : public CombatInventoryItemMagic
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_CombatInventoryItemPotion;
		SKYRIM_ADDR static auto VTABLE = VTABLE_CombatInventoryItemPotion;

		~CombatInventoryItemPotion() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE GetType() override;                                  // 09 - { return 7; }
		bool CheckBusy(CombatController* a_controller) override;  // 0E
	};
	static_assert(sizeof(CombatInventoryItemPotion) == 0x50);
}
