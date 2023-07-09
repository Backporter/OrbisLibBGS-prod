#pragma once

#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class MapMenu;

	class MapInputHandler : public MenuEventHandler
	{
	public:
		virtual ~MapInputHandler();
	public:
		MapMenu* mapMenu;
	};
	static_assert(sizeof(MapInputHandler) == 0x18);
}