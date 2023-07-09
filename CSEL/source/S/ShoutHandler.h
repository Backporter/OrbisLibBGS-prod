#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class ShoutHandler : public PlayerInputHandler
	{
	public:
		virtual ~ShoutHandler();

		bool CanProcess(InputEvent* a_event) override;
	};
}