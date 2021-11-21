#include "RE/E/Effect.h"

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
}
