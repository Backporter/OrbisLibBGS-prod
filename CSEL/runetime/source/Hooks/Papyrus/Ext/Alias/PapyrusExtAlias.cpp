#include "../Alias/PapyrusExtAlias.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSBaseAlias.h"
#include "../../../../../../source/T/TESQuest.h"

#include "../../../../../../Build/Flags.h"
#include "../../../../../../EXTERNAL/SKSE/SKSE.h"

namespace PapyrusExtAlias
{
	// I really hate doing this...
	using namespace ConsoleRE;

	BSFixedString GetName(BGSBaseAlias* thisAlias)
	{
		return (thisAlias) ? thisAlias->aliasName.m_data : NULL;
	}

	uint32_t GetId(BGSBaseAlias* thisAlias)
	{
		return (thisAlias) ? thisAlias->aliasID : -1;
	}

	void RegisterForKey(BGSBaseAlias * thisAlias, uint32_t key)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Register<BGSBaseAlias>(key, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForKey(BGSBaseAlias * thisAlias, uint32_t key)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Unregister<BGSBaseAlias>(key, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForAllKeys(BGSBaseAlias * thisAlias)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->UnregisterAll<BGSBaseAlias>(BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void RegisterForControl(BGSBaseAlias * thisAlias, BSFixedString control)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Register<BGSBaseAlias>(control, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForControl(BGSBaseAlias * thisAlias, BSFixedString control)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Unregister<BGSBaseAlias>(control, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForAllControls(BGSBaseAlias * thisAlias)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->UnregisterAll<BGSBaseAlias>(BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void RegisterForMenu(BGSBaseAlias * thisAlias, BSFixedString menuName)
	{
		if (!thisAlias || !menuName.m_data)
			return;

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Register<BGSBaseAlias>(menuName, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForMenu(BGSBaseAlias * thisAlias, BSFixedString menuName)
	{
		if (!thisAlias || !menuName.m_data)
			return;

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Unregister<BGSBaseAlias>(menuName, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForAllMenus(BGSBaseAlias * thisAlias)
	{
		if (!thisAlias)
			return;

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->UnregisterAll<BGSBaseAlias>(BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void RegisterForModEvent(BGSBaseAlias * thisAlias, BSFixedString eventName, BSFixedString callbackName)
	{
		if (!thisAlias || !eventName.m_data || !callbackName.m_data)
			return;

#if USE_SKSE_ADDON
		SKSE::ModCallbackParameters params;
		params.m_callbackName = callbackName;
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Register<BGSBaseAlias>(eventName, BGSBaseAlias::TypeID, thisAlias, &params);
#endif
	}

	void UnregisterForModEvent(BGSBaseAlias * thisAlias, BSFixedString eventName)
	{
		if (!thisAlias || !eventName.m_data)
			return;

#if USE_SKSE_ADDON
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Register<BGSBaseAlias>(eventName, BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void UnregisterForAllModEvents(BGSBaseAlias * thisAlias)
	{
#if USE_SKSE_ADDON
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->UnregisterAll<BGSBaseAlias>(BGSBaseAlias::TypeID, thisAlias);
#endif
	}

	void SendModEvent(BGSBaseAlias * thisAlias, BSFixedString eventName, BSFixedString strArg, float numArg)
	{
		if (!thisAlias || !eventName.m_data)
			return;

#if USE_SKSE_ADDON
		SKSE::ModCallbackEvent evn(eventName, strArg, numArg, thisAlias->owningQuest);
		SKSE::ModCallbackEventDispatcher::GetSingleton()->SendEventSink(&evn);
#endif
	}

	void RegisterForCameraState(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Register<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void UnregisterForCameraState(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Unregister<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void RegisterForCrosshairRef(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Register<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void UnregisterForCrosshairRef(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Unregister<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void RegisterForActorAction(BGSBaseAlias * thisForm, uint32_t actionType)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Register<BGSBaseAlias>(actionType, BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void UnregisterForActorAction(BGSBaseAlias * thisForm, uint32_t actionType)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Unregister<BGSBaseAlias>(actionType, BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void UnregisterForNiNodeUpdate(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Unregister<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	void RegisterForNiNodeUpdate(BGSBaseAlias * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Register<BGSBaseAlias>(BGSBaseAlias::TypeID, thisForm);
#endif
	}

	bool RegisterAlias(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetName),                   BGSBaseAlias, BSFixedString>                            ("GetName",                   "Alias", GetName));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetId),                     BGSBaseAlias, uint32_t>                                 ("GetId",                     "Alias", GetId));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForKey),            BGSBaseAlias, void, uint32_t>                           ("RegisterForKey",            "Alias", RegisterForKey));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForKey),          BGSBaseAlias, void, uint32_t>                           ("UnregisterForKey",          "Alias", UnregisterForKey));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForAllKeys),      BGSBaseAlias, void>                                     ("UnregisterForAllKeys",      "Alias", UnregisterForAllKeys));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForMenu),           BGSBaseAlias, void, BSFixedString>                      ("RegisterForMenu",           "Alias", RegisterForMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForMenu),         BGSBaseAlias, void, BSFixedString>                      ("UnregisterForMenu",         "Alias", UnregisterForMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForAllMenus),     BGSBaseAlias, void>                                     ("UnregisterForAllMenus",     "Alias", UnregisterForAllMenus));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForModEvent),       BGSBaseAlias, void, BSFixedString, BSFixedString>       ("RegisterForModEvent",       "Alias", RegisterForModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForModEvent),     BGSBaseAlias, void, BSFixedString>                      ("UnregisterForModEvent",     "Alias", UnregisterForModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForAllModEvents), BGSBaseAlias, void>                                     ("UnregisterForAllModEvents", "Alias", UnregisterForAllModEvents));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SendModEvent),              BGSBaseAlias, void, BSFixedString, BSFixedString, float>("SendModEvent",              "Alias", SendModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForControl),        BGSBaseAlias, void, BSFixedString>                      ("RegisterForControl",        "Alias", RegisterForControl));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForControl),      BGSBaseAlias, void, BSFixedString>                      ("UnregisterForControl",      "Alias", UnregisterForControl));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForAllControls),  BGSBaseAlias, void>                                     ("UnregisterForAllControls",  "Alias", UnregisterForAllControls));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForCameraState),    BGSBaseAlias, void>                                     ("RegisterForCameraState",    "Alias", RegisterForCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForCameraState),  BGSBaseAlias, void>                                     ("UnregisterForCameraState",  "Alias", UnregisterForCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForCrosshairRef),   BGSBaseAlias, void>                                     ("RegisterForCrosshairRef",   "Alias", RegisterForCrosshairRef));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForCrosshairRef), BGSBaseAlias, void>                                     ("UnregisterForCrosshairRef", "Alias", UnregisterForCrosshairRef));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForActorAction),    BGSBaseAlias, void, uint32_t>                           ("RegisterForActorAction",    "Alias", RegisterForActorAction));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForActorAction),  BGSBaseAlias, void, uint32_t>                           ("UnregisterForActorAction",  "Alias", UnregisterForActorAction));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegisterForNiNodeUpdate),   BGSBaseAlias, void>                                     ("RegisterForNiNodeUpdate",   "Alias", RegisterForNiNodeUpdate));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UnregisterForNiNodeUpdate), BGSBaseAlias, void>                                     ("UnregisterForNiNodeUpdate", "Alias", UnregisterForNiNodeUpdate));

		VM->SetCallableFromTasklets("Alias", "RegisterForKey", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForKey", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForAllKeys", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForMenu", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForMenu", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForAllMenus", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForModEvent", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForAllModEvents", true);
		VM->SetCallableFromTasklets("Alias", "SendModEvent", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForControl", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForControl", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForAllControls", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForCameraState", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForCameraState", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForCrosshairRef", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForCrosshairRef", true);
		VM->SetCallableFromTasklets("Alias", "RegisterForActorAction", true);
		VM->SetCallableFromTasklets("Alias", "UnregisterForActorAction", true);

		return true;
	}
}