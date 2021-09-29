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

	bool TaskQueueInterface::ShouldUseTaskQueue()
	{
		using func_t = decltype(&TaskQueueInterface::ShouldUseTaskQueue);
		REL::Relocation<func_t> func{ REL::ID(38079) };
		return func();
	}

	std::uint32_t TaskQueueInterface::QueueBulletWaterDisplacementTask(float a_scale, const NiPoint3& a_pos)
	{
		using func_t = decltype(&TaskQueueInterface::QueueBulletWaterDisplacementTask);
		REL::Relocation<func_t> func{ REL::ID(35978) };
		return func(this, a_scale, a_pos);
	}
}
