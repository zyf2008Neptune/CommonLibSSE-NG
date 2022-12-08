#include "RE/Q/QuestStatus.h"

#include "Offsets.h"

namespace RE
{
	BSTEventSource<QuestStatus::Event>* QuestStatus::GetEventSource()
	{
		using func_t = decltype(&QuestStatus::GetEventSource);
		REL::Relocation<func_t> func{ 24719, 25196 };
		return func();
	}
}
