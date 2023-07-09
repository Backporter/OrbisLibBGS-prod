#pragma once

#include <stdint.h>


namespace ConsoleRE
{
	class ExtraAnimNoteReceiver
	{
	public:
		ExtraAnimNoteReceiver();
		virtual ~ExtraAnimNoteReceiver();
	public:
		uint8_t ExtraAnimNoteReceiverPad[0x18];
	};
	static_assert(sizeof(ExtraAnimNoteReceiver) == 0x20, "##############");
}