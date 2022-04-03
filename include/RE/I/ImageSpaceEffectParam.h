#pragma once

namespace RE
{
	class ImageSpaceEffectParam
	{
	public:
		inline static auto RTTI = RTTI_ImageSpaceEffectParam;

		virtual ~ImageSpaceEffectParam();  // 00
	};
	static_assert(sizeof(ImageSpaceEffectParam) == 0x8);
}
