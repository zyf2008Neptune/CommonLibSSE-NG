#pragma once

namespace RE
{
	namespace BSScript
	{
		class IVMDebugInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScriptːːIVMDebugInterface;

			virtual ~IVMDebugInterface();  // 00

			// add
			virtual void Unk_01(void) = 0;  // 01
		};
		static_assert(sizeof(IVMDebugInterface) == 0x8);
	}
}
