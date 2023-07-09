#pragma once
#include "../P/PlayerInputHandler.h"

namespace ConsoleRE
{
	class ReadyWeaponHandler : public PlayerInputHandler
	{
	public:
		virtual ~ReadyWeaponHandler();
		bool CanProcess(InputEvent* a_event) override;
	};
}