#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESObjectMISC.h"
#include "RE/T/TESQualityForm.h"

namespace RE
{
	class BGSApparatus :
		public TESObjectMISC,   // 000
		public TESQualityForm,  // 100
		public TESDescription   // 110
	{
	public:
		SKYRIM_ADDR static auto           RTTI = RTTI_BGSApparatus;
		SKYRIM_ADDR static auto           VTABLE = VTABLE_BGSApparatus;
		inline static constexpr auto FORMTYPE = FormType::Apparatus;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSApparatus() override;  // 00

		// override (TESObjectMISC)
		bool Load(TESFile* a_mod) override;  // 06
	};
	static_assert(sizeof(BGSApparatus) == 0x120);
}
