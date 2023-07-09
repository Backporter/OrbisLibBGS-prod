#pragma once

#include "../B/BSTEvent.h"

namespace ConsoleRE
{
	struct ChestsLooted
	{
	public:
		struct Event
		{
		public:
		};
	public:
		static BSTEventSource<Event>* GetEventSource();
		static void                   SendEvent();
	};
}