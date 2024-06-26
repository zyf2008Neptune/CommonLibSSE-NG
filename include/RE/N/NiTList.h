#pragma once

#include "RE/N/NiTDefaultAllocator.h"
#include "RE/N/NiTPointerListBase.h"

namespace RE
{
	template <class T>
	class NiTList : public NiTPointerListBase<NiTDefaultAllocator<T>, T>
	{
	public:
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiTList<void*>) == 0x18);
}
