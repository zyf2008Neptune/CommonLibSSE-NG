#pragma once

namespace RE
{
	class hkpCdBody;

	struct hkpShapeRayCastCollectorOutput;

	class hkpRayHitCollector
	{
	public:
		inline static auto RTTI = RTTI_hkpRayHitCollector;

		// add
		virtual void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) = 0;  // 00

		virtual ~hkpRayHitCollector() = default;  // 01

		// members
		float         earlyOutHitFraction;  // 08
		std::uint32_t pad0C;                // 0C
	};
	static_assert(sizeof(hkpRayHitCollector) == 0x10);
}
