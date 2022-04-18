#pragma once

namespace RE
{
	class NiBoneMatrixSetterI
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_NiBoneMatrixSetterI;

		virtual ~NiBoneMatrixSetterI();  // 00

		// add
		virtual void Unk_01(void);  // 01
	};
	static_assert(sizeof(NiBoneMatrixSetterI) == 0x8);
}
