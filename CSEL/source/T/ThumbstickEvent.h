#pragma once

#include "../I/IDEvent.h"
#include <stdint.h>

namespace ConsoleRE
{
	class ThumbstickEvent : public IDEvent
	{
	public:
		struct InputTypes
		{
			enum InputType : uint32_t
			{
				kLeftThumbstick = 0x0B,
				kRightThumbstick = 0x0C
			};
		};
		using InputType = InputTypes::InputType;
	public:
		bool IsLeft(void) { return idCode == InputType::kLeftThumbstick; }
		bool IsRight(void) { return idCode == InputType::kRightThumbstick; }
	public:
		float x;
		float y;
	};
	static_assert(sizeof(ThumbstickEvent) == 0x30, "#");
}