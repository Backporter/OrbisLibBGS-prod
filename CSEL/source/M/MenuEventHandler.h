#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	class ButtonEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
	class ThumbstickEvent;

	class MenuEventHandler : public BSIntrusiveRefCounted
	{
	public:
		MenuEventHandler() = default;
		virtual ~MenuEventHandler() = default;

		// add 
		virtual bool CanProcess(InputEvent* a_event) = 0;
		virtual bool ProcessButton(ButtonEvent* a_event);
		virtual bool ProcessMouseMove(MouseMoveEvent* a_event);
		virtual bool ProcessThumbstick(ThumbstickEvent* a_event);
		virtual bool ProcessKinect(KinectEvent* a_event);
	public:
		bool          registered;
		uint8_t		  Unk0D;
		uint16_t	  Unk0E;
	};
	static_assert(sizeof(MenuEventHandler) == 0x10);
}