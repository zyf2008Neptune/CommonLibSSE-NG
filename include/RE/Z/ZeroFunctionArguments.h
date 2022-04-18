#pragma once

#include "RE/I/IFunctionArguments.h"

namespace RE
{
	namespace BSScript
	{
		class ZeroFunctionArguments : public IFunctionArguments
		{
		public:
			SKYRIM_ADDR static auto RTTI = RTTI_BSScript__ZeroFunctionArguments;

			// override (IFunctionArguments)
			bool operator()(BSScrapArray<Variable>& a_dst) const override;  // 01
		};
		static_assert(sizeof(ZeroFunctionArguments) == 0x8);
	}
}
