#pragma once

#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class HeldStateHandler : public PlayerInputHandler
	{
	public:
		~HeldStateHandler() override;
		
		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event);
		virtual void SetHeldStateActive(bool a_flag);
	public:
		bool heldStateActive;
		bool triggerReleaseEvent;
	};
	static_assert(sizeof(PlayerInputHandler) == 0x10);
}