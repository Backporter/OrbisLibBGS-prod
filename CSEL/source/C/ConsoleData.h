#pragma once

#include "../B/BSString.h"
#include "../I/IUIMessageData.h"

namespace ConsoleRE
{
	class NiBinaryStream;

	class ConsoleData : public IUIMessageData
	{
	public:
		~ConsoleData() override;
	public:
		BSString*									str;
		int32_t										pickRef;
		uint32_t									pad1C;
		NiBinaryStream*								file;
		uint32_t									type;
		uint32_t									pad2C;
	};
	static_assert(sizeof(ConsoleData) == 0x30);
}