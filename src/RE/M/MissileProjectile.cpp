#pragma once

#include "RE/M/MissileProjectile.h"

using namespace REL;

namespace RE
{
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
	void MissileProjectile::Unk_C2()
	{
		RelocateVirtual<decltype(&MissileProjectile::Unk_C2)>(0xC2, 0xC3, this);
	}

	void MissileProjectile::Unk_C3()
	{
		RelocateVirtual<decltype(&MissileProjectile::Unk_C3)>(0xC3, 0xC4, this);
	}
#endif
}
