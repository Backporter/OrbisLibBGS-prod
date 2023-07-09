#pragma once

#include "../A/ActorValues.h"
#include "../H/HUDMeter.h"

namespace ConsoleRE
{
	class ActorValueMeter : public HUDMeter
	{
	public:
		~ActorValueMeter() override;
	public:
		ActorValue    actorValue;
	};
}