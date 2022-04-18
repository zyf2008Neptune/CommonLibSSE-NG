#pragma once

#include "RE/B/bhkCharacterState.h"

namespace RE
{
	class bhkCharacterStateClimbing : public bhkCharacterState
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_bhkCharacterStateClimbing;

		~bhkCharacterStateClimbing() override;  // 00

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;  // 03 - { return kClimbing; }
		void                  Unk_08(void) override;     // 08
	};
	static_assert(sizeof(bhkCharacterStateClimbing) == 0x10);
}
