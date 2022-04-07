#include "RE/L/LockpickingMenu.h"

#include "RE/T/TESObjectREFR.h"

namespace RE
{
	TESObjectREFR* LockpickingMenu::GetTargetReference()
	{
		REL::Relocation<TESObjectREFRPtr*> refptr{ REL::RelocationID(519716, 406271) };
		return refptr->get();
	}
}
