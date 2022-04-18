#pragma once

namespace RE
{
	class BGSPerkEntry;

	class PerkEntryVisitor
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_PerkEntryVisitor;

		enum class ReturnType
		{
			kBreak,
			kContinue
		};

		virtual ReturnType Visit(BGSPerkEntry* a_perkEntry) = 0;  // 00
	};
}
