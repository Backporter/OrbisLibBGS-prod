#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class IUIMessageData
	{
	public:
		virtual ~IUIMessageData() = default;
	public:
		uint8_t  Unk08;
		uint8_t  Unk09;
		uint16_t pad0A;
	};
	static_assert(sizeof(IUIMessageData) == 0x10);
}