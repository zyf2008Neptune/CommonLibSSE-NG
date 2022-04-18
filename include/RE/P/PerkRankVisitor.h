#pragma once

#include "RE/B/BGSPerkRankArray.h"

namespace RE
{
	struct PerkRankData;

	class PerkRankVisitor
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_PerkRankVisitor;

		virtual bool operator()(const PerkRankData* a_entry) = 0;  // 00
	};
}
