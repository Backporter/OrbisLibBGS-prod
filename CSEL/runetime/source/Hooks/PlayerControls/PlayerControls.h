#pragma once

#include "../../../../source/P/PlayerControls.h"

namespace RunetimePlayerControls
{
	using RegisterPlayerControlls_t = void(ConsoleRE::PlayerControls*);
	extern Relocation<RegisterPlayerControlls_t*> _RegisterPlayerControlls;

	void RegisterPlayerControls(ConsoleRE::PlayerControls* a_this);
}