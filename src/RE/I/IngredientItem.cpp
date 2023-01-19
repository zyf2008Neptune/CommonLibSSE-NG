#include "RE/I/IngredientItem.h"

#include "RE/E/Effect.h"

namespace RE
{
	// 14097CD70 (1.5.97)
	bool IngredientItem::IsHostile() const
	{
		return this->hostileCount > 0;
	}

	// 1400FF120 (1.5.97)
	bool IngredientItem::LearnEffect(std::uint32_t a_aiIndex)
	{
		if (a_aiIndex < 4) {
			this->gamedata.knownEffectFlags |= 1 << a_aiIndex;
			this->AddChange(0x80000000);
			return true;
		}
		return false;
	}

	bool IngredientItem::LearnEffect(RE::EffectSetting* a_effect)
	{
		if (!a_effect) {
			return false;
		}
		std::uint32_t aiIndex = 0;
		for (auto effect : this->effects) {
			if (effect->baseEffect == a_effect) {
				LearnEffect(aiIndex);
				return true;
			}
			aiIndex++;
		}
		return false;
	}

	// 1400FF1A0 (1.5.97)
	int IngredientItem::LearnNextEffect()
	{
		long flags = this->gamedata.knownEffectFlags;
		auto aiIndex = 0;
		while ((flags & 1 << aiIndex) != 0) {
			if (++aiIndex >= 4) {
				return -1;
			}
		}
		LearnEffect(aiIndex);
		return aiIndex;
	}

	// 1400FF150 (1.5.97)
	void IngredientItem::LearnAllEffects()
	{
		for (std::uint32_t aiIndex = 0; aiIndex < 4; ++aiIndex) {
			LearnEffect(aiIndex);
		}
	}
}
