#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CraftingSubMenu.h"
#include "RE/I/IMessageBoxCallback.h"

namespace RE::CraftingSubMenus
{
	class AlchemyMenu : public CraftingSubMenu
	{
	public:
		inline static constexpr auto RTTI = RTTI_CraftingSubMenus__AlchemyMenu;

		class QuitMenuCallback : public IMessageBoxCallback
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__AlchemyMenu__QuitMenuCallback;

			~QuitMenuCallback() override;  // 00

			// override (IMessageBoxCallback)
			void Run(Message a_msg) override;  // 01

			// members
			AlchemyMenu* subMenu;  // 10
		};
		static_assert(sizeof(QuitMenuCallback) == 0x18);

		struct EntryData
		{
			RE::InventoryEntryData* ingredient{ nullptr };  // 00
			std::uint32_t           filterFlag{ 0 };        // 08
			bool                    selected{ false };      // 0c: Whether ingredient has been selected for the potion.
			std::uint8_t            enabled{ true };        // 0d: Whether ingredient is allowed to be selected or is disabled.
			std::uint16_t           pad0A;                  // 0e
		};
		static_assert(sizeof(EntryData) == 0x10);

		struct EffectData
		{
			std::uint32_t unk0;  // 0
			std::uint32_t unk4;  // 4
			std::int32_t  unk8;  // 8
		};
		static_assert(sizeof(EffectData) == 0xC);

		~AlchemyMenu() override;  // 00

		// override (CraftingSubMenu)
		void Accept(CallbackProcessor* a_cbReg) override;  // 01
		void Unk_05(void) override;                        // 05

		// members
		RE::BSTArray<EntryData>  ingredientsList;          // 100
		std::int32_t             unk118;                   // 118
		std::int32_t             unk11c;                   // 11c
		std::uint32_t            ingredientIndex1;         // 120
		std::uint32_t            ingredientIndex2;         // 124
		std::uint32_t            ingredientIndex3;         // 128
		std::uint32_t            unk12c;                   // 12c
		std::uint32_t            selectedIngredientCount;  // 130
		std::uint32_t            unk134;                   // 134
		RE::BSTArray<EffectData> effectData;               // 138
		std::uint64_t            unk150;                   // 150
		RE::GFxValue             unk158;                   // 158
		std::uint64_t            unk170;                   // 170
		RE::TESForm*             outputPotion;             // 178
		RE::TESForm*             outputPotion2;            // 180
		std::uint32_t            unk188;                   // 188
		std::uint32_t            unk18c;                   // 18c
		RE::BSFixedString        unk190;                   // 190
		std::uint64_t            unk198;                   // 198
	};
	static_assert(sizeof(AlchemyMenu) == 0x1A0);
}