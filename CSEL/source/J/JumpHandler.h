#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class JumpHandler : public PlayerInputHandler
	{
	public:
		~JumpHandler() override;

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	};
	static_assert(sizeof(JumpHandler) == 0x10);
}