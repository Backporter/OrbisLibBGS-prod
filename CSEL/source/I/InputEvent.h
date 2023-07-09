#pragma once

#include "../B/BSFixedString.h"
#include "../I/InputDevices.h"

#include <stdint.h>

namespace ConsoleRE
{
	enum class INPUT_EVENT_TYPE
	{
		kButton = 0,
		kMouseMove,
		kChar,
		kThumbstick,
		kDeviceConnect,
		kKinect
	};

	class ButtonEvent;
	class IDEvent;

	class InputEvent
	{
	public:
		virtual ~InputEvent();

		// add
		virtual bool					HasIDCode(void);
		virtual const BSFixedString&	QUserEvent();
	
		//
		constexpr INPUT_DEVICE		GetDevice() const noexcept { return device; }
		constexpr INPUT_EVENT_TYPE  GetEventType() const noexcept { return eventType; }
	public:
		INPUT_DEVICE		 device;
		INPUT_EVENT_TYPE	 eventType;
		InputEvent*			 next;
	};
	static_assert(sizeof(InputEvent) == 0x18);
}