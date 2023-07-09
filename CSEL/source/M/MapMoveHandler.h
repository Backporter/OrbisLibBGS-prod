#pragma once

#include "../M/MapInputHandler.h"

namespace ConsoleRE
{
	class MapMoveHandler : public MapInputHandler
	{
	public:
		~MapMoveHandler() override;

		// override (MapInputHandler)
		bool CanProcess(InputEvent*) override;
		bool ProcessThumbstick(ThumbstickEvent*) override;
	public:
		uint64_t unk18;
	};
	static_assert(sizeof(MapMoveHandler) == 0x20);

}