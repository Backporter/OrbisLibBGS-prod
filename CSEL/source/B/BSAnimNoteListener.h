#pragma once

#include "../B/BSAnimNote.h"
#include "../N/NiTArray.h"

namespace ConsoleRE
{
	class IBSAnimNoteReceiver;

	class BSAnimNoteListener
	{
	public:
		struct BSAnimReceiverType
		{
		public:
			uint32_t			 noteType;
			uint32_t			 pad04;
			IBSAnimNoteReceiver* receiver;
		};
		static_assert(sizeof(BSAnimReceiverType) == 0x10);
	public:
		NiTPrimitiveArray<BSAnimReceiverType*> receivers;
	};
	static_assert(sizeof(BSAnimNoteListener) == 0x18);
}