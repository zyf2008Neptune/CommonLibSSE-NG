#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	struct ChestsLooted
	{
	public:
		struct Event
		{
		public:
		};
		static_assert(std::is_empty_v<Event>);

		static BSTEventSource<Event>* GetEventSource();
		static void                   SendEvent();

	private:
		KEEP_FOR_RE()
	};
	static_assert(std::is_empty_v<ChestsLooted>);
}
