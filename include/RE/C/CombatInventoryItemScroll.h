#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemScroll : public CombatInventoryItemMagic
	{
	public:
		inline static auto RTTI = RTTI_CombatInventoryItemScroll;
		inline static auto VTABLE = VTABLE_CombatInventoryItemScroll;

		~CombatInventoryItemScroll() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE GetType() override;                                  // 09 - { return 8; }
		bool CheckBusy(CombatController* a_controller) override;  // 0E
	};
	static_assert(sizeof(CombatInventoryItemScroll) == 0x50);
}
