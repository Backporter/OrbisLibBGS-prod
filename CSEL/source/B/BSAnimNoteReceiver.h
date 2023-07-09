#pragma once
#include <stdint.h>
namespace ConsoleRE
{
	class BSAnimNoteReceiver
	{
	public:
		BSAnimNoteReceiver();
		virtual ~BSAnimNoteReceiver();
	public:
		uint8_t BSAnimNoteReceiverPad[0x28];
	};
	static_assert(sizeof(BSAnimNoteReceiver) == 0x28, "####################");
}