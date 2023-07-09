#pragma once

#include "../M/MapInputHandler.h"

namespace ConsoleRE
{
	class MapZoomHandler : public MapInputHandler
	{
	public:
		~MapZoomHandler() override;

		// override (MapInputHandler)
		bool CanProcess(InputEvent*) override;
		bool ProcessButton(ButtonEvent*) override;
	};
	static_assert(sizeof(MapZoomHandler) == 0x18);
}