#include "RE/C/ContainerMenu.h"

namespace RE
{
	ContainerMenu::ContainerMode ContainerMenu::GetContainerMode()
	{
#ifndef SKYRIMVR
		REL::Relocation<ContainerMode*> mode{ REL::ID(519396) };
#else
		REL::Relocation<ContainerMode*> mode{ REL::Offset(0x3011720) };
#endif
		return *mode;
	}

	RefHandle ContainerMenu::GetTargetRefHandle()
	{
#ifndef SKYRIMVR
		REL::Relocation<RefHandle*> handle{ REL::ID(519421) };
#else
		REL::Relocation<RefHandle*>     handle{ REL::Offset(0x30117e8) };
#endif
		return *handle;
	}
}
