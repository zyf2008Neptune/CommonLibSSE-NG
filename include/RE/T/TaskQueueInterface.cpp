#include "RE/T/TaskQueueInterface.h"

namespace RE
{
	TaskQueueInterface* TaskQueueInterface::GetSingleton()
	{
#ifndef SKYRIMVR
		REL::Relocation<TaskQueueInterface**> singleton{ REL::ID(517228) };
#else
		REL::Relocation<TaskQueueInterface**> singleton{ 0x2ffd778 };
#endif
		return *singleton;
	}
}
