#pragma once

#include "../B/BSString.h"
#include "../I/IUIMessageData.h"

namespace ConsoleRE
{
	class HUDData :	public IUIMessageData
	{
	public:
		~HUDData() override;
	public:
		uint32_t	type;
		uint32_t	pad14;
		BSString	text;
		uint32_t	unk28;
		uint32_t	pad2C;
		void*		unk30;
		uint64_t	unk38;
		uint8_t		unk40;
		uint8_t		pad41;
		uint16_t	pad42;
		uint32_t	discovery;
	};
	static_assert(sizeof(HUDData) == 0x40);
}