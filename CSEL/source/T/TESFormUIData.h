#pragma once

#include "../I/IUIMessageData.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESFormUIData : public IUIMessageData
	{
	public:
		~TESFormUIData() override;
	public:
		uint64_t Unk10;
	};
	static_assert(sizeof(TESFormUIData) == 0x18);
}