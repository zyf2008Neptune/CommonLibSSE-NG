#include "RE/C/ContainerMenu.h"

namespace RE
{
	ContainerMenu::ContainerMode ContainerMenu::GetContainerMode()
	{
		REL::Relocation<ContainerMode*> mode{ REL::RelocationID(519396, 405937) };
		return *mode;
	}

	RefHandle ContainerMenu::GetTargetRefHandle()
	{
		REL::Relocation<RefHandle*> handle{ REL::RelocationID(519421, 405962) };
		return *handle;
	}
}
