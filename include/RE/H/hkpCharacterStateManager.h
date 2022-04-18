#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkpCharacterState.h"

namespace RE
{
	class hkpCharacterStateManager : public hkReferencedObject
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_hkpCharacterStateManager;

		~hkpCharacterStateManager() override;  // 00

		// members
		hkpCharacterState* registeredState[hkpCharacterStateType::kTotal];  // 00
	};
	static_assert(sizeof(hkpCharacterStateManager) == 0x68);
}
