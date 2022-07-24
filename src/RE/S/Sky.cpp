#include "RE/S/Sky.h"

#include "RE/T/TESWeather.h"

namespace RE
{
	Sky* Sky::GetSingleton()
	{
		using func_t = decltype(&Sky::GetSingleton);
		REL::Relocation<func_t> func{ Offset::Sky::GetSingleton };
		return func();
	}

	bool Sky::IsRaining() const
	{
		if (currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy) && ((currentWeather->data.precipitationBeginFadeIn * 0.0039215689f) * 0.999f) < currentWeatherPct) {
			return true;
		}
		if (!lastWeather || lastWeather->data.flags.none(TESWeather::WeatherDataFlag::kRainy) || (((lastWeather->data.precipitationEndFadeOut * 0.0039215689f) * 0.999f) + 0.001) <= currentWeatherPct) {
			return false;
		}
		return true;
	}

	bool Sky::IsSnowing() const
	{
		if (currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow) && ((currentWeather->data.precipitationBeginFadeIn * 0.0039215689f) * 0.999f) < currentWeatherPct) {
			return true;
		}
		if (!lastWeather || lastWeather->data.flags.none(TESWeather::WeatherDataFlag::kSnow) || (((lastWeather->data.precipitationEndFadeOut * 0.0039215689f) * 0.999f) + 0.001f) <= currentWeatherPct) {
			return false;
		}
		return true;
	}
}
