#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/S/SkyObject.h"

namespace RE
{
	class NiNode;

	class Stars : public SkyObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_Stars;
		inline static constexpr auto VTABLE = VTABLE_Stars;

		~Stars() override;  // 00

		// override (SkyObject)
		void Init(NiNode* a_root) override;              // 02
		void Update(Sky* a_sky, float a_arg2) override;  // 03

		// members
		NiPointer<NiNode> stars;  // 10
		float             alpha;  // 18
		std::uint32_t     pad1C;  // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(Stars) == 0x20);
}
