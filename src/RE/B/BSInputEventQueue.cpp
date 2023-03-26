#include "RE/B/BSInputEventQueue.h"

namespace RE
{
	BSInputEventQueue* BSInputEventQueue::GetSingleton()
	{
		REL::Relocation<BSInputEventQueue**> singleton{ RELOCATION_ID(520856, 407374) };
		return *singleton;
	}

	void BSInputEventQueue::EnqueueButtonEvent(INPUT_DEVICE device, std::uint32_t buttonId, float value, float heldDownSecs)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueButtonEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67382, 68685) };
		return func(this, device, buttonId, value, heldDownSecs);
	}

	void BSInputEventQueue::EnqueueCharEvent(std::uint32_t keycode)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueCharEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67383, 68686) };
		return func(this, keycode);
	}

	void BSInputEventQueue::EnqueueMouseMoveEvent(std::int32_t deltaX, std::int32_t deltaY)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueMouseMoveEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67384, 68687) };
		return func(this, deltaX, deltaY);
	}

	void BSInputEventQueue::EnqueueThumbstickEvent(std::uint32_t thumbstickId, float x, float y)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueThumbstickEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67385, 68688) };
		return func(this, thumbstickId, x, y);
	}

	void BSInputEventQueue::EnqueueDeviceConnectEvent(INPUT_DEVICE device, bool connected)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueDeviceConnectEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67386, 68689) };
		return func(this, device, connected);
	}

	void BSInputEventQueue::EnqueueKinectEvent(BSFixedString* userEvent, BSFixedString* heard)
	{
		using func_t = decltype(&BSInputEventQueue::EnqueueKinectEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(67387, 68690) };
		return func(this, userEvent, heard);
	}

	void BSInputEventQueue::Reset()
	{
		using func_t = decltype(&BSInputEventQueue::Reset);
		REL::Relocation<func_t> func{ RELOCATION_ID(67388, 68691) };
		return func(this);
	}
}
