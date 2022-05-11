#include "RE/E/Effect.h"

#include "RE/E/EffectSetting.h"

namespace RE
{
	Effect::EffectItem::EffectItem() :
		magnitude(0.0),
		area(0),
		duration(0)
	{}

	Effect::Effect() :
		effectItem(),
		pad0C(0),
		baseEffect(nullptr),
		cost(0.0),
		pad1C(0),
		conditions()
	{}
	bool Effect::IsMatch(EffectSetting* a_base, float a_mag, std::uint32_t a_area, std::uint32_t a_dur, float a_cost)
	{
		namespace FLOAT = SKSE::stl::numeric;

		return baseEffect == a_base &&
		       FLOAT::essentially_equal(effectItem.magnitude, a_mag) && effectItem.area == a_area && effectItem.duration == a_dur && FLOAT::essentially_equal(cost, a_cost);
	}

		float Effect::GetMagnitude() const
		{
			if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoMagnitude)) {
				return 0.0f;
			}
			return effectItem.magnitude;
		}

		std::uint32_t Effect::GetArea() const
		{
			if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoArea)) {
				return 0;
			}
			return effectItem.area;
		}

		std::uint32_t Effect::GetDuration() const
		{
			if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoDuration)) {
				return 0;
			}
			return effectItem.duration;
		}

		bool Effect::IsHostile() const
		{
			return baseEffect->IsHostile();
		}
	}
