#pragma once

#include "../I/IUIMessageData.h"
#include <stdint.h>

namespace ConsoleRE
{
	class RefHandleUIData : public IUIMessageData
	{
	public:
		~RefHandleUIData() override;
	public:
		uint32_t refHandle;
	};
	static_assert(sizeof(RefHandleUIData) == 0x10);
}