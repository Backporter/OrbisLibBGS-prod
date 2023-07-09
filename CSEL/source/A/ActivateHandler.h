#pragma once

#include "../H/HeldStateHandler.h"

namespace ConsoleRE
{
	class ActivateHandler : public HeldStateHandler
	{
	public:
		~ActivateHandler() override;
		
		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;
	public:
		bool heldButtonActionSuccess;
		bool disabled;
	};
	static_assert(sizeof(ActivateHandler) == 0x10);
}