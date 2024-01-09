#pragma once

namespace RE
{
	class TESBoundObject;
	class TESObjectREFR;

	namespace SendUIMessage
	{
		void SendInventoryUpdateMessage(TESObjectREFR* a_inventoryRef, const TESBoundObject* a_updateObj)
		{
			using func_t = decltype(&SendUIMessage::SendInventoryUpdateMessage);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51911, 52849) };
			return func(a_inventoryRef, a_updateObj);
		}
	}
}
