#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	class ExtraReferenceHandle : public BSExtraData
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_ExtraReferenceHandle;
		SKYRIM_ADDR static auto VTABLE = VTABLE_ExtraReferenceHandle;
		inline static auto      EXTRADATATYPE = ExtraDataType::kReferenceHandle;

		ExtraReferenceHandle();
		explicit ExtraReferenceHandle(ObjectRefHandle a_containerRef);
		virtual ~ExtraReferenceHandle() = default;  // 00

		// override (BSExtraData)
		virtual ExtraDataType GetType() const override;                             // 01 - { return kReferenceHandle; }
		virtual bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return containerRef != a_rhs->containerRef; }

		NiPointer<TESObjectREFR> GetOriginalReference();

		// members
		ObjectRefHandle containerRef;  // 10
		std::uint32_t   pad14;         // 14
	};
	static_assert(sizeof(ExtraReferenceHandle) == 0x18);
}
