#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class SyncQueueObj : public BSIntrusiveRefCounted
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_SyncQueueObj;

		virtual ~SyncQueueObj();  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01

		// members
		std::uint32_t unk0C;  // 0C
	};
	static_assert(sizeof(SyncQueueObj) == 0x10);
}
