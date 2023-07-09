#pragma once

#include "../H/HeldStateHandler.h"

namespace ConsoleRE
{
	class TogglePOVHandler : public HeldStateHandler
	{
	public:
		~TogglePOVHandler() override;
		
		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	public:
		bool pressRegistered;
	};
	static_assert(sizeof(TogglePOVHandler) == 0x10);
}