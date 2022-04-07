#include "RE/B/BSResponse.h"

namespace RE
{
	ResponseDictionary* ResponseDictionary::GetSingleton()
	{
		REL::Relocation<ResponseDictionary**> singleton{ REL::RelocationID(517372, 403902) };
		return *singleton;
	}
}
