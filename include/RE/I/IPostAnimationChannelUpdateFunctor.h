#pragma once

namespace RE
{
	class IPostAnimationChannelUpdateFunctor
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_IPostAnimationChannelUpdateFunctor;

		virtual ~IPostAnimationChannelUpdateFunctor();  // 00

		// add
		virtual void Unk_01(void);  // 01
	};
	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x8);
}
