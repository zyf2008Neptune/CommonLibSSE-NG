#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemStaff : public CombatInventoryItemMagic
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_CombatInventoryItemStaff;
		SKYRIM_ADDR static auto VTABLE = VTABLE_CombatInventoryItemStaff;

		~CombatInventoryItemStaff() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE       GetType() override;   // 09 - { return 6; }
		MagicItem* GetMagic() override;  // 16
	};
	static_assert(sizeof(CombatInventoryItemStaff) == 0x50);
}
