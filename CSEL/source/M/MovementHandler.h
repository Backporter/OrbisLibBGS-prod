#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class MovementHandler : public PlayerInputHandler
	{
	public:
		~MovementHandler() override;

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	public:
	};
	static_assert(sizeof(MovementHandler) == 0x10);

}