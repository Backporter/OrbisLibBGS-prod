#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class AutoMoveHandler : public PlayerInputHandler
	{
	public:
		virtual ~AutoMoveHandler();

		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	};
	static_assert(sizeof(AutoMoveHandler) == 0x10, "");
}