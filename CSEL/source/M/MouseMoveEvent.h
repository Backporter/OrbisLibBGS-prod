#pragma once

#include "../I/IDEvent.h"

namespace ConsoleRE
{
	class MouseMoveEvent : public IDEvent
	{
	public:
		~MouseMoveEvent() override;
	public:
		int32_t mouseInputX;
		int32_t mouseInputY;
	};
	static_assert(sizeof(MouseMoveEvent) == 0x30);
}