#pragma once

#include "../I/InputEvent.h"

namespace ConsoleRE
{
	class DeviceConnectEvent : public InputEvent
	{
	public:
		~DeviceConnectEvent() override;
	public:
		bool	 connected;
		uint8_t	 pad19;
		uint16_t pad1A;
		uint32_t pad1C;
	};
	static_assert(sizeof(DeviceConnectEvent) == 0x20);
}