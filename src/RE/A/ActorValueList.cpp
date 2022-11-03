#include "RE/A/ActorValueList.h"

#include "RE/A/ActorValueInfo.h"

namespace RE
{
	ActorValueInfo* ActorValueList::GetActorValue(ActorValue a_actorValue) const
    {
		return a_actorValue < ActorValue::kTotal ?
		           actorValues[stl::to_underlying(a_actorValue)] :
		           nullptr;
	}

	ActorValue ActorValueList::LookupActorValueByName(std::string_view a_enumName) const
    {
		for (std::uint32_t i = 0; i < 164; ++i) {
			if (a_enumName.size() == strlen(actorValues[i]->enumName) &&
				_strnicmp(actorValues[i]->enumName, a_enumName.data(), a_enumName.size()) == 0) {
				return static_cast<ActorValue>(i);
			}
		}
		return ActorValue::kNone;
	}
}
