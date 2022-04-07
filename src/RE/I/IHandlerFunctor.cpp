#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	HandlerDictionary* HandlerDictionary::GetSingleton()
	{
		REL::Relocation<HandlerDictionary**> singleton{ REL::RelocationID(518086, 404607) };
		return *singleton;
	}
}
