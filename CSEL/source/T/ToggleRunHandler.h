#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class ToggleRunHandler : public PlayerInputHandler
	{
	public:
		~ToggleRunHandler() override;
		
		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	};
	static_assert(sizeof(ToggleRunHandler) == 0x10);
}