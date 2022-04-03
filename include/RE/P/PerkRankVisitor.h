#pragma once

#include "RE/B/BGSPerkRankArray.h"

namespace RE
{
	struct PerkRankData;

	class PerkRankVisitor
	{
	public:
		inline static auto RTTI = RTTI_PerkRankVisitor;

		virtual bool operator()(const PerkRankData* a_entry) = 0;  // 00
	};
}
