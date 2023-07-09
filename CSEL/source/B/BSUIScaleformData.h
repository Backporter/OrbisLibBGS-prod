#pragma once

#include "../I/IUIMessageData.h"

namespace ConsoleRE
{
	class GFxEvent;

	class BSUIScaleformData : public IUIMessageData
	{
	public:
		~BSUIScaleformData() override;
	public:
		GFxEvent* scaleformEvent;
	};
	static_assert(sizeof(BSUIScaleformData) == 0x18);
}