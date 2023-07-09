#include "../../../../../OrbisUtil/include/Relocation.h"
#include "../../../../../OrbisUtil/include/INIHandler.h"
#include "../../../../../OrbisUtil/include/Logger.h"

#include "../../../../Build/Flags.h"

#include "../../../Internal/PluginManger.h"


#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

#include "PlayerControls.h"
#include "../Events/Events.h"

namespace RunetimePlayerControls
{
	Relocation<RegisterPlayerControlls_t*> _RegisterPlayerControlls;

	void RegisterPlayerControls(ConsoleRE::PlayerControls* a_this)
	{
		_RegisterPlayerControlls(a_this);

		auto* UISingleton = ConsoleRE::UI::GetSingleton();
		if (UISingleton)
		{
			UISingleton->GetEventSource<ConsoleRE::MenuOpenCloseEvent>()->AddEventSink(Events::MenuEventHandler::GetSingleton());
		}

#if USE_SKSE_ADDON
		SKSE::ModCallbackEventDispatcher::GetSingleton()->AddEventSink(SKSE::ModCallbackEventHandler::GetSingelton());
		SKSE::CameraEventDispatcher::GetSingleton()->AddEventSink(SKSE::CameraEventHandler::GetSingelton());
		SKSE::CrosshairRefDispatcher::GetSingleton()->AddEventSink(SKSE::CrosshairRefEventHandler::GetSingelton());
		SKSE::ActionEventDispatcher::GetSingleton()->AddEventSink(SKSE::ActionEventHandler::GetSingelton());
		SKSE::NinodeUpdateDispatcher::GetSingleton()->AddEventSink(SKSE::NiNodeUpdateEventHandler::GetSingelton());
#endif
		auto* InputDeviceSingleton = ConsoleRE::BSInputDeviceManager::GetSingleton();
		if (InputDeviceSingleton)
		{
			InputDeviceSingleton->AddEventSink(Events::InputEventHandler::GetSingleton());
		}

		Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kInput, 0, 0, 0);
	}
}