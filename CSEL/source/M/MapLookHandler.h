#pragma once

#include "../M/MapInputHandler.h"

namespace ConsoleRE
{
	class MapLookHandler : public MapInputHandler
	{
	public:
		virtual ~MapLookHandler();

		// override (MenuEventHandler)
		bool ProcessThumbstick(ThumbstickEvent*) override;
		bool ProcessMouseMove(MouseMoveEvent*) override;
		bool ProcessButton(ButtonEvent*) override;
	public:
		uint64_t unk18;
	};
	static_assert(sizeof(MapLookHandler) == 0x20);
}