#include "RE/G/GiftMenu.h"

namespace RE
{
	RefHandle GiftMenu::GetTargetRefHandle()
	{
		REL::Relocation<RefHandle*> handle{ REL::RelocationID(519570, 406111) };
		return *handle;
	}
}
