#pragma once

#include "../T/ThirdPersonState.h"

namespace ConsoleRE
{
	class HorseCameraState : public ThirdPersonState
	{
	public:
		~HorseCameraState() override;
	public:
		uint32_t		horseRefHandle;
		float           horseCurrentDirection;
	};
}