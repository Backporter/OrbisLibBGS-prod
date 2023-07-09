#include "../C/ChestsLooted.h"

namespace ConsoleRE
{
	BSTEventSource<ChestsLooted::Event>* ChestsLooted::GetEventSource()
	{
		Relocation<BSTEventSource<ChestsLooted::Event>*> singleton("", 0x3199250);
		return singleton.get();
	}

	void ChestsLooted::SendEvent()
	{
		const Event e{};
		auto        source = GetEventSource();
		if (source) 
		{
			source->SendEventSink(&e);
		}
	}
}