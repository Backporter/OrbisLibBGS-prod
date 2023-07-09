#pragma once

namespace ConsoleRE
{
	struct AITimeStamp
	{
	public:
		float timeStamp;
	};
	static_assert(sizeof(AITimeStamp) == 0x4);
}