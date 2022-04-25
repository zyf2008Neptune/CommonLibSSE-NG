#include "RE/B/BookMenu.h"

#include "RE/T/TESObjectREFR.h"

namespace RE
{
	TESObjectBOOK* BookMenu::GetTargetForm()
	{
		REL::Relocation<TESObjectBOOK**> book{ RELOCATION_ID(519295, 405835) };
		return *book;
	}

	TESObjectREFR* BookMenu::GetTargetReference()
	{
		REL::Relocation<TESObjectREFRPtr*> refptr{ RELOCATION_ID(519300, 405840) };
		return refptr->get();
	}
}
