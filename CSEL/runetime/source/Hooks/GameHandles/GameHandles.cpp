#include "GameHandles.h"

#include "../../../../../OrbisUtil/include/Macro.h"
#include "../../../../../OrbisUtil/include/Relocation.h"
#include "../../../../../OrbisUtil/include/MemoryHandler.h"
#include "../../../../../OrbisUtil/include/Trampoline.h"

#include "../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

namespace GameHandles
{
	// handlers
	Relocation<uintptr_t> WeaponRightSwingHandlervtbl			("", 0x1D6CB68);
	Relocation<uintptr_t> WeaponLeftSwingHandlervtbl			("", 0x1D6CBA8);
	Relocation<uintptr_t> RightHandSpellFireHandlervtbl			("", 0x1D6CA28);
	Relocation<uintptr_t> LeftHandSpellFireHandlervtbl			("", 0x1D6C9E8);
	Relocation<uintptr_t> RightHandSpellCastHandlervtbl			("", 0x1D6CAE8);
	Relocation<uintptr_t> LeftHandSpellCastHandlervtbl			("", 0x1D6CAA8);
	Relocation<uintptr_t> VoiceSpellCastHandlervtbl				("", 0x1D6CB28);
	Relocation<uintptr_t> VoiceSpellFireHandlervtbl				("", 0x1D6CA68);
	Relocation<uintptr_t> BowDrawnHandlervtbl					("", 0x1D6D428);
	Relocation<uintptr_t> BowReleaseHandlervtbl					("", 0x1D6D468);
	Relocation<uintptr_t> WeaponBeginDrawRightHandlervtbl		("", 0x1D6CBE8);
	Relocation<uintptr_t> WeaponBeginSheatheRightHandlervtbl	("", 0x1D6CC28);
	Relocation<uintptr_t> RightHandWeaponDrawHandlervtbl		("", 0x1D6CCE8);
	Relocation<uintptr_t> RightHandWeaponSheatheHandlervtbl		("", 0x1D6CD28);

#if USE_SKSE_ADDON
	static uint8_t RightHandWeaponSheatheHandlerHook(ConsoleRE::RightHandWeaponSheatheHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx)
	{ 
		return SKSE::RightHandWeaponSheatheHandler::get()->Process(rsi, rdx);
	}

	static uint8_t RightHandWeaponDrawHandlerHook(ConsoleRE::RightHandWeaponDrawHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::RightHandWeaponDrawHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t WeaponBeginSheatheRightHandlerHook(ConsoleRE::WeaponBeginSheatheRightHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::WeaponBeginSheatheRightHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t WeaponBeginDrawRightHandlerHook(ConsoleRE::WeaponBeginDrawRightHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::WeaponBeginDrawRightHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t BowReleaseHandlerHook(ConsoleRE::BowReleaseHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::BowReleaseHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t BowDrawnHandlerHook(ConsoleRE::BowDrawnHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx)
	{ 
		return SKSE::BowDrawnHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t VoiceSpellFireHandlerHook(ConsoleRE::VoiceSpellFireHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx)
	{ 
		return SKSE::VoiceSpellFireHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t VoiceSpellCastHandlerHook(ConsoleRE::VoiceSpellCastHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::VoiceSpellCastHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t LeftHandSpellCastHandlerHook(ConsoleRE::LeftHandSpellCastHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx)
	{ 
		return SKSE::LeftHandSpellCastHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t RightHandSpellCastHandlerHook(ConsoleRE::RightHandSpellCastHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::RightHandSpellCastHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t LeftHandSpellFireHandlerHook(ConsoleRE::LeftHandSpellFireHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::LeftHandSpellFireHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t RightHandSpellFireHandlerHook(ConsoleRE::RightHandSpellFireHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::RightHandSpellFireHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t WeaponLeftSwingHandlerHook(ConsoleRE::WeaponLeftSwingHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::WeaponLeftSwingHandler::get()->Process(rsi, rdx); 
	}

	static uint8_t WeaponRightSwingHandlerHook(ConsoleRE::WeaponRightSwingHandler* const, ConsoleRE::Actor* rsi, const ConsoleRE::BSFixedString& rdx) 
	{ 
		return SKSE::WeaponRightSwingHandler::get()->Process(rsi, rdx); 
	}
#endif


	void Apply()
	{
#if USE_SKSE_ADDON
	 xUtilty::safe_write<uintptr_t>(WeaponRightSwingHandlervtbl.address(),				FN_AS_RAW_ADDRESS(WeaponRightSwingHandlerHook));
	 xUtilty::safe_write<uintptr_t>(WeaponLeftSwingHandlervtbl.address(),				FN_AS_RAW_ADDRESS(WeaponLeftSwingHandlerHook));
	 xUtilty::safe_write<uintptr_t>(RightHandSpellFireHandlervtbl.address(),			FN_AS_RAW_ADDRESS(RightHandSpellFireHandlerHook));
	 xUtilty::safe_write<uintptr_t>(LeftHandSpellFireHandlervtbl.address(),				FN_AS_RAW_ADDRESS(LeftHandSpellFireHandlerHook));
	 xUtilty::safe_write<uintptr_t>(RightHandSpellCastHandlervtbl.address(),			FN_AS_RAW_ADDRESS(RightHandSpellCastHandlerHook));
	 xUtilty::safe_write<uintptr_t>(LeftHandSpellCastHandlervtbl.address(),				FN_AS_RAW_ADDRESS(LeftHandSpellCastHandlerHook));
	 xUtilty::safe_write<uintptr_t>(VoiceSpellCastHandlervtbl.address(),				FN_AS_RAW_ADDRESS(VoiceSpellCastHandlerHook));
	 xUtilty::safe_write<uintptr_t>(VoiceSpellFireHandlervtbl.address(),				FN_AS_RAW_ADDRESS(VoiceSpellFireHandlerHook));
	 xUtilty::safe_write<uintptr_t>(BowDrawnHandlervtbl.address(),						FN_AS_RAW_ADDRESS(BowDrawnHandlerHook));
	 xUtilty::safe_write<uintptr_t>(BowReleaseHandlervtbl.address(),					FN_AS_RAW_ADDRESS(BowReleaseHandlerHook));
	 xUtilty::safe_write<uintptr_t>(WeaponBeginDrawRightHandlervtbl.address(),			FN_AS_RAW_ADDRESS(WeaponBeginDrawRightHandlerHook));
	 xUtilty::safe_write<uintptr_t>(WeaponBeginSheatheRightHandlervtbl.address(),		FN_AS_RAW_ADDRESS(WeaponBeginSheatheRightHandlerHook));
	 xUtilty::safe_write<uintptr_t>(RightHandWeaponDrawHandlervtbl.address(),			FN_AS_RAW_ADDRESS(RightHandWeaponDrawHandlerHook));
	 xUtilty::safe_write<uintptr_t>(RightHandWeaponSheatheHandlervtbl.address(),		FN_AS_RAW_ADDRESS(RightHandWeaponSheatheHandlerHook));
#endif
	}
}