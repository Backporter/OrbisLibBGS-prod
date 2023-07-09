#include "../ActiveEffect/PapyrusExtActiveEffect.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/A/ActiveEffect.h"

#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../Build/Flags.h"
#include "../../../../../../EXTERNAL/SKSE/SKSE.h"

namespace PapyrusExtActiveEffect
{
	// I really hate doing this...
	using namespace ConsoleRE;

	float GetTimeElapsed(ActiveEffect* effect)
	{
		return (effect) ? effect->elapsedSeconds : 0.0;
	}

	float GetDuration(ActiveEffect* effect)
	{
		return (effect) ? effect->duration : 0.0;
	}
	
	float GetMagnitude(ActiveEffect* effect)
	{
		return (effect) ? effect->magnitude : 0.0;
	}

	void RegisterForKey(ActiveEffect * effect, uint32_t key)
	{
		if (!effect)
			return;

		// PRINT_FMT("key %d", key)

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Register<ActiveEffect>(key, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForKey(ActiveEffect * effect, uint32_t key)
	{
		if (!effect)
			return;

		// PRINT_FMT("key %d", key)

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Unregister<ActiveEffect>(key, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForAllKeys(ActiveEffect * effect)
	{
		if (!effect)
			return;
#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->UnregisterAll<ActiveEffect>(ActiveEffect::TypeID, effect);
#endif
	}

	void RegisterForControl(ActiveEffect * effect, BSFixedString control)
	{
		if (!effect)
			return;

		// PRINT_FMT("control %s", control.m_data)

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Register<ActiveEffect>(control, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForControl(ActiveEffect * effect, BSFixedString control)
	{
		if (!effect)
			return;

		// PRINT_FMT("control %s", control.m_data)

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Unregister<ActiveEffect>(control, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForAllControls(ActiveEffect * effect)
	{
		if (!effect)
			return;

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->UnregisterAll<ActiveEffect>(ActiveEffect::TypeID, effect);
#endif
	}

	void RegisterForMenu(ActiveEffect * effect, BSFixedString menuName)
	{
		if (!effect || !menuName.m_data)
			return;

		// PRINT_FMT("%s", menuName.m_data);

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Register<ActiveEffect>(menuName, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForMenu(ActiveEffect * effect, BSFixedString menuName)
	{
		if (!effect || !menuName.m_data)
			return;

		// PRINT_FMT("%s", menuName.m_data);

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Unregister<ActiveEffect>(menuName, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForAllMenus(ActiveEffect * effect)
	{
		if (!effect)
			return;

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->UnregisterAll<ActiveEffect>(ActiveEffect::TypeID, effect);
#endif
	}

	void RegisterForModEvent(ActiveEffect* effect, BSFixedString eventName, BSFixedString callbackName)
	{
		if (!effect || !eventName.m_data || !callbackName.m_data)
			return;

		// PRINT_FMT("%s %s", eventName.m_data, callbackName.m_data);

#if USE_SKSE_ADDON
		SKSE::ModCallbackParameters params;
		params.m_callbackName = callbackName;
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Register<ActiveEffect>(eventName, ActiveEffect::TypeID, effect, &params);
#endif
	}

	void UnregisterForModEvent(ActiveEffect * effect, BSFixedString eventName)
	{
		if (!effect || !eventName.m_data)
			return;

		// PRINT_FMT("%s", eventName.m_data);

#if USE_SKSE_ADDON
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Unregister<ActiveEffect>(eventName, ActiveEffect::TypeID, effect);
#endif
	}

	void UnregisterForAllModEvents(ActiveEffect * effect)
	{
#if USE_SKSE_ADDON
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->UnregisterAll<ActiveEffect>(ActiveEffect::TypeID, effect);
#endif
	}

	void SendModEvent(ActiveEffect * thisForm, BSFixedString eventName, BSFixedString strArg, float numArg)
	{
		if (!eventName.m_data)
			return;

		// PRINT_FMT("%s %s 0x%lx", eventName.m_data, strArg.m_data, numArg);

#if USE_SKSE_ADDON
		SKSE::ModCallbackEvent evn(eventName, strArg, numArg, NULL);
		SKSE::ModCallbackEventDispatcher::GetSingleton()->SendEventSink(&evn);
#endif
	}

	//
	void RegisterForCameraState(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Register<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}

	void UnregisterForCameraState(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Unregister<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}

	void RegisterForCrosshairRef(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Register<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}

	void UnregisterForCrosshairRef(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Unregister<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}

	void RegisterForActorAction(ActiveEffect * thisForm, uint32_t actionType)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Register<ActiveEffect>(actionType, ActiveEffect::TypeID, thisForm);
#endif
	}

	void UnregisterForActorAction(ActiveEffect * thisForm, uint32_t actionType)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Unregister<ActiveEffect>(actionType, ActiveEffect::TypeID, thisForm);
#endif
	}

	void UnregisterForNiNodeUpdate(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Unregister<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}

	void RegisterForNiNodeUpdate(ActiveEffect * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Register<ActiveEffect>(ActiveEffect::TypeID, thisForm);
#endif
	}
	//

	bool RegisterActiveEffect(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetTimeElapsed),				ActiveEffect, float>									("GetTimeElapsed",			  "ActiveMagicEffect", GetTimeElapsed));
	    VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetDuration),					ActiveEffect, float>									("GetDuration",				  "ActiveMagicEffect", GetDuration));
	    VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetMagnitude),				ActiveEffect, float>									("GetMagnitude",			  "ActiveMagicEffect", GetMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForKey),				ActiveEffect, void, uint32_t>							("RegisterForKey",			  "ActiveMagicEffect", RegisterForKey));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForKey),			ActiveEffect, void, uint32_t>							("UnregisterForKey",		  "ActiveMagicEffect", UnregisterForKey));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForAllKeys),		ActiveEffect, void>										("UnregisterForAllKeys",	  "ActiveMagicEffect", UnregisterForAllKeys));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForMenu),				ActiveEffect, void, BSFixedString>					    ("RegisterForMenu",			  "ActiveMagicEffect", RegisterForMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForMenu),			ActiveEffect, void, BSFixedString>					    ("UnregisterForMenu",		  "ActiveMagicEffect", UnregisterForMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForAllMenus),		ActiveEffect, void>									    ("UnregisterForAllMenus",	  "ActiveMagicEffect", UnregisterForAllMenus));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForModEvent),			ActiveEffect, void, BSFixedString, BSFixedString>	    ("RegisterForModEvent",		  "ActiveMagicEffect", RegisterForModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForModEvent),		ActiveEffect, void, BSFixedString>					    ("UnregisterForModEvent",	  "ActiveMagicEffect", UnregisterForModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForAllModEvents),	ActiveEffect, void>									    ("UnregisterForAllModEvents", "ActiveMagicEffect", UnregisterForAllModEvents));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(SendModEvent),				ActiveEffect, void, BSFixedString, BSFixedString, float>("SendModEvent",		      "ActiveMagicEffect", SendModEvent));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForControl),			ActiveEffect, void, BSFixedString>						("RegisterForControl",        "ActiveMagicEffect", RegisterForControl));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForControl),		ActiveEffect, void, BSFixedString>						("UnregisterForControl",      "ActiveMagicEffect", UnregisterForControl));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForAllControls),	ActiveEffect, void>										("UnregisterForAllControls",  "ActiveMagicEffect", UnregisterForAllControls));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForCameraState),		ActiveEffect, void>                                     ("RegisterForCameraState",    "ActiveMagicEffect", RegisterForCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForCameraState),	ActiveEffect, void>                                     ("UnregisterForCameraState",  "ActiveMagicEffect", UnregisterForCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForCrosshairRef),		ActiveEffect, void>                                     ("RegisterForCrosshairRef",   "ActiveMagicEffect", RegisterForCrosshairRef));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForCrosshairRef),	ActiveEffect, void>                                     ("UnregisterForCrosshairRef", "ActiveMagicEffect", UnregisterForCrosshairRef));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForActorAction),		ActiveEffect, void, uint32_t>                           ("RegisterForActorAction",    "ActiveMagicEffect", RegisterForActorAction));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForActorAction),	ActiveEffect, void, uint32_t>                           ("UnregisterForActorAction",  "ActiveMagicEffect", UnregisterForActorAction));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(RegisterForNiNodeUpdate),		ActiveEffect, void>                                     ("RegisterForNiNodeUpdate",   "ActiveMagicEffect", RegisterForNiNodeUpdate));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UnregisterForNiNodeUpdate),	ActiveEffect, void>                                     ("UnregisterForNiNodeUpdate", "ActiveMagicEffect", UnregisterForNiNodeUpdate));

		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForKey",					true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForKey",				true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForAllKeys",			true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForMenu",					true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForMenu",				true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForAllMenus",			true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForModEvent",				true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForAllModEvents",		true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "SendModEvent",					true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForControl",				true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForControl",			true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForAllControls",		true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForCameraState",		    true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForCameraState",	    true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForCrosshairRef",			true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForCrosshairRef",	    true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "RegisterForActorAction",		    true);
		VM->SetCallableFromTasklets("ActiveMagicEffect", "UnregisterForActorAction",	    true);

		return true;
	}
}