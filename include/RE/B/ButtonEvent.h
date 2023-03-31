#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IDEvent.h"
#include "RE/I/InputEvent.h"
#include "RE/M/MemoryManager.h"
#include "RE/V/VRWandEvent.h"

namespace RE
{
#ifndef ENABLE_SKYRIM_VR
	class ButtonEvent : public IDEvent
#else
	class ButtonEvent : public VRWandEvent
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_ButtonEvent;
		inline static constexpr auto VTABLE = VTABLE_ButtonEvent;

		~ButtonEvent() override;  // 00

		[[nodiscard]] constexpr float Value() const noexcept { return value; }
		[[nodiscard]] constexpr float HeldDuration() const noexcept { return heldDownSecs; }
		[[nodiscard]] constexpr bool  IsPressed() const noexcept { return Value() > 0.0F; }
		[[nodiscard]] constexpr bool  IsRepeating() const noexcept { return HeldDuration() > 0.0F; }
		[[nodiscard]] constexpr bool  IsDown() const noexcept { return IsPressed() && (HeldDuration() == 0.0F); }
		[[nodiscard]] constexpr bool  IsHeld() const noexcept { return IsPressed() && IsRepeating(); }
		[[nodiscard]] constexpr bool  IsUp() const noexcept { return (Value() == 0.0F) && IsRepeating(); }

		// members
		float value;         // 28
		float heldDownSecs;  // 2C

		static ButtonEvent* Create(INPUT_DEVICE a_inputDevice, const BSFixedString& a_userEvent, uint32_t a_idCode, float a_value, float a_heldDownSecs)
		{
			auto buttonEvent = malloc<ButtonEvent>(sizeof(ButtonEvent));
			std::memset(reinterpret_cast<void*>(buttonEvent), 0, sizeof(ButtonEvent));
			if (buttonEvent) {
				stl::emplace_vtable<ButtonEvent>(buttonEvent);
				buttonEvent->device = a_inputDevice;
				buttonEvent->eventType = INPUT_EVENT_TYPE::kButton;
				buttonEvent->next = nullptr;
				buttonEvent->userEvent = a_userEvent;
				buttonEvent->idCode = a_idCode;
				buttonEvent->value = a_value;
				buttonEvent->heldDownSecs = a_heldDownSecs;
			}
			return buttonEvent;
		}
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(ButtonEvent) == 0x30);
#else
	static_assert(sizeof(ButtonEvent) == 0x38);
#endif
}
