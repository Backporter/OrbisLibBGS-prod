#pragma once

namespace ConsoleRE
{
	class hkStepInfo
	{
	public:
		float  startTime;
		float  endTime;
		float  deltaTime;
		float  invDeltaTime;
	};
	static_assert(sizeof(hkStepInfo) == 0x10, "");
}