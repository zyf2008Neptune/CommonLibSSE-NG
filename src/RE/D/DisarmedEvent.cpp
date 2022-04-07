#include "RE/D/DisarmedEvent.h"

namespace RE
{
	BSTEventSource<DisarmedEvent::Event>* DisarmedEvent::GetEventSource()
	{
		using func_t = decltype(&DisarmedEvent::GetEventSource);
		REL::Relocation<func_t> func{ REL::RelocationID(37392, 38340) };
		return func();
	}
}
