#pragma once

#include "../I/IDEvent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class ButtonEvent : public IDEvent
	{
	public:
		~ButtonEvent() override;

		constexpr float Value() const noexcept { return value; }
		constexpr float HeldDuration() const noexcept { return heldDownSecs; }
		constexpr bool	IsPressed() const noexcept { return Value() > 0.0F; }
		constexpr bool	IsRepeating() const noexcept { return HeldDuration() > 0.0F; }
		constexpr bool	IsDown() const noexcept { return IsPressed() && (HeldDuration() == 0.0F); }
		constexpr bool	IsHeld() const noexcept { return IsPressed() && IsRepeating(); }
		constexpr bool	IsUp() const noexcept { return (Value() == 0.0F) && IsRepeating(); }
		
		static ButtonEvent* Create(INPUT_DEVICE a_inputDevice, const BSFixedString& a_userEvent, uint32_t a_idCode, float a_value, float a_heldDownSecs)
		{
			ButtonEvent* buttonEvent = (ButtonEvent*)malloc(sizeof(ButtonEvent));
			if (buttonEvent)
			{
				memset((void*)buttonEvent, 0, sizeof(ButtonEvent));
				memcpy((void*)buttonEvent, (const void*)RTTI_ButtonEvent.get(), 8);

				buttonEvent->device			= a_inputDevice;
				buttonEvent->eventType		= INPUT_EVENT_TYPE::kButton;
				buttonEvent->next			= nullptr;
				buttonEvent->userEvent		= a_userEvent;
				buttonEvent->idCode			= a_idCode;
				buttonEvent->value			= a_value;
				buttonEvent->heldDownSecs	= a_heldDownSecs;
			}

			return buttonEvent;
		}
	public:
		float value;
		float heldDownSecs;
	};
	static_assert(sizeof(ButtonEvent) == 0x30);

}