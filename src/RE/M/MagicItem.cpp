#include "RE/M/MagicItem.h"

namespace RE
{
	float MagicItem::CalculateMagickaCost(Actor* a_caster) const
	{
		return CalculateCost(a_caster);
	}

	float MagicItem::CalculateTotalGoldValue(Actor* a_caster) const
	{
		return CalculateCost(a_caster);
	}

	MagicItem::MagicItemDataCollector MagicItem::CollectData() const
	{
		MagicItemDataCollector ans(this);
		this->VisitEffects(ans);
		return ans;
	}

	EffectSetting* MagicItem::GetAVEffectSetting() const
	{
		using func_t = decltype(&MagicItem::GetAVEffectSetting);
		REL::Relocation<func_t> func{ Offset::MagicItem::GetAVEffectSetting };
		return func(this);
	}

	Effect* MagicItem::GetCostliestEffectItem(MagicSystem::Delivery a_delivery, bool a_positiveArea) const
	{
		using func_t = decltype(&MagicItem::GetCostliestEffectItem);
		REL::Relocation<func_t> func{ Offset::MagicItem::GetCostliestEffectItem };
		return func(this, a_delivery, a_positiveArea);
	}

	float MagicItem::CalculateCost(Actor* a_caster) const
	{
		using func_t = decltype(&MagicItem::CalculateTotalGoldValue);
		REL::Relocation<func_t> func{ Offset::MagicItem::CalculateCost };
		return func(this, a_caster);
	}

	auto MagicItem::GetData()
		-> Data*
	{
		return GetData2();
	}

	auto MagicItem::GetData() const
		-> const Data*
	{
		return GetData1();
	}

	uint32_t MagicItem::GetLargestArea() const
	{
		using func_t = decltype(&MagicItem::GetLargestArea);
		REL::Relocation<func_t> func{ RELOCATION_ID(11219, 0) };  // I do not know for AE
		return func(this);
	}

	uint32_t MagicItem::GetLongestDuration() const
	{
		using func_t = decltype(&MagicItem::GetLongestDuration);
		REL::Relocation<func_t> func{ RELOCATION_ID(11218, 0) };  // I do not know for AE
		return func(this);
	}

	bool MagicItem::IsPermanent() const
	{
		using func_t = decltype(&MagicItem::IsPermanent);
		REL::Relocation<func_t> func{ RELOCATION_ID(11183, 11290) };
		return func(this);
	}

	void MagicItem::VisitEffects(MagicItemTraversalFunctor& visitor) const
	{
		using func_t = decltype(&MagicItem::VisitEffects);
		REL::Relocation<func_t> func{ RELOCATION_ID(11222, 0) };  // I do not know for AE
		return func(this, visitor);
	}

	MagicItem::MagicItemDataCollector::MagicItemDataCollector(const MagicItem* a_mitem)
	{
		using func_t = void (MagicItemDataCollector* a, const MagicItem* a_mitem);
		REL::Relocation<func_t> func{ RELOCATION_ID(33407, 0) };  // I do not know for AE
		func(this, a_mitem);
	}
}
