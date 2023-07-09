#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class ButtonEvent;
	class InputEvent;
	class MouseMoveEvent;
	class PlayerControlsData;
	class ThumbstickEvent;

	class PlayerInputHandler
	{
	public:
		virtual ~PlayerInputHandler();
		
		// add
		virtual bool CanProcess(InputEvent* a_event) = 0;
		virtual void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data);
		virtual void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data);
		virtual void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data);
	public:
		bool inputEventHandlingEnabled;
	};
	static_assert(sizeof(PlayerInputHandler) == 0x10);
}