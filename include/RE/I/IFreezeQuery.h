#pragma once

namespace RE
{
	namespace BSScript
	{
		class IFreezeQuery
		{
		public:
			SKYRIM_ADDR static auto RTTI = RTTI_BSScript__IFreezeQuery;

			virtual ~IFreezeQuery();  // 00

			// add
			virtual void Unk_01(void) = 0;  // 00
		};
		static_assert(sizeof(IFreezeQuery) == 0x8);
	}
}
