#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiTransform
	{
	public:
		constexpr NiTransform() noexcept;

		NiTransform Invert() const;

		bool        operator==(const NiTransform& a_rhs) const;
		bool        operator!=(const NiTransform& a_rhs) const;
		NiTransform operator*(const NiTransform& a_rhs) const;
		NiPoint3    operator*(const NiPoint3& a_point) const;

		NiMatrix3 rotate;     // 00
		NiPoint3  translate;  // 24
		float     scale;      // 30
	};
	static_assert(sizeof(NiTransform) == 0x34);
}
