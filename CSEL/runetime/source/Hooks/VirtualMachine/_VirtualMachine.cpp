#include "_VirtualMachine.h"

#include "../../../../source/V/VirtualMachine.h"

#include "../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

#include "../../../Internal/Interfaces/SerializationInterface/Serialization/Serialization.h"

namespace VirtualMachine
{
	Relocation<bfunc_t*> LoadGameFunc;		// 0xAF97E0 - 1.09
	Relocation<bfunc_t*> SaveGameFunc;		// 0xAF80B0 - 1.09
	Relocation<vfunc_t*> ReverGameFunc;		// 0xAF50A0 - 1.09
	Relocation<ffunc_t*> FormDeletionFunc;	// 0xAEACD0 - 1.09

	bool LoadGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, void* a_unk2, void* a_unk3)
	{
		//
		bool ret = LoadGameFunc(a_this, a_unk2, a_unk3);
		
		//
		return ret;
	}

	bool SaveGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, void* a_unk2, void* a_unk3)
	{
		//
		bool ret = SaveGameFunc(a_this, a_unk2, a_unk3);

		//
		return ret;
	}

	void RevertGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this)
	{
		//
		ReverGameFunc(a_this);
	}

	void FormDeletionHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, uint64_t handle)
	{
		//
		FormDeletionFunc(a_this, handle);

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->UnregisterAll(handle);
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->UnregisterAll(handle);
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->UnregisterAll(handle);
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->UnregisterAll(handle);
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->UnregisterAll(handle);
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Unregister(handle);
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Unregister(handle);
#endif
	}
}