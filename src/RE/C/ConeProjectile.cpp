#pragma once

#include "RE/C/ConeProjectile.h"

using namespace REL;

namespace RE
{
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
	void ConeProjectile::Unk_C2()
	{
		RelocateVirtual<decltype(&ConeProjectile::Unk_C2)>(0xC2, 0xC3, this);
	}
#endif
}
