#pragma once

namespace ConsoleRE
{
	struct TESWaitStopEvent
	{
	public:
		bool interrupted;
	};
	static_assert(sizeof(TESWaitStopEvent) == 0x1);
}
