#pragma once

namespace RE
{
	class IMovementInterface
	{
	public:
		inline static auto RTTI = RTTI_IMovementInterface;

		virtual ~IMovementInterface();
	};
	static_assert(sizeof(IMovementInterface) == 0x8);
}
