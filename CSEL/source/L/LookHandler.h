#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	struct LookHandler : public PlayerInputHandler
	{
	public:
		~LookHandler() override;

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data) override;
	};
	static_assert(sizeof(LookHandler) == 0x10);
}