#pragma once

#include "RE/G/GRefCountImplCore.h"

namespace RE
{
	class GRefCountImpl : GRefCountImplCore
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_GRefCountImpl;

		~GRefCountImpl() override = default;  // 00

		void AddRef();
		void Release();
	};
	static_assert(sizeof(GRefCountImpl) == 0x10);
}
