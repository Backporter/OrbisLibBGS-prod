#pragma once

#include "../../../../../OrbisUtil/include/SystemWrapper.h"

#include "../../../../source/B/BSTEvent.h"
#include "../../../../source/I/InputEvent.h"
#include "../../../../source/B/ButtonEvent.h"
#include "../../../../source/T/ThumbstickEvent.h"
#include "../../../../source/M/MenuOpenCloseEvent.h"
#include "../../../../source/B/BSInputDeviceManager.h"
#include "../../../../source/E/EventFunctor.h"

#include "../../Hooks/Scaleform/ext/ScaleFormALL.h"

#include "../../../../Build/Flags.h"
#include "../../../../EXTERNAL/SKSE/SKSE.h"

// Global namespace for events/event classes/etc
namespace Events
{
	// MenuEventHandler
	class MenuEventHandler : public ConsoleRE::BSTEventSink<ConsoleRE::MenuOpenCloseEvent>
	{
	public:
		static MenuEventHandler* GetSingleton()
		{
			static MenuEventHandler Singleton;
			return &Singleton;
		}
		
		ConsoleRE::BSEventNotifyControl	ProcessEvent(const ConsoleRE::MenuOpenCloseEvent* a_event, ConsoleRE::BSTEventSource<ConsoleRE::MenuOpenCloseEvent>* a_source) override
		{
			if (!a_event || !a_source)
				return ConsoleRE::BSEventNotifyControl::kContinue;

			ConsoleRE::BSFixedString type = a_event->opening ? "OnMenuOpen" : "OnMenuClose";

#if USE_SKSE_ADDON
			auto EQF = SKSE::EventQueueFunctor1<ConsoleRE::BSFixedString>(type, a_event->menuName);
			SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->ForEach(a_event->menuName, EQF);
#endif
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};

	// InputEventHandler
	class InputEventHandler : public ConsoleRE::BSTEventSink<ConsoleRE::InputEvent*>
	{
	public:
		static InputEventHandler* GetSingleton()
		{
			static InputEventHandler Singleton;
			return &Singleton;
		}

		ConsoleRE::BSEventNotifyControl ProcessEvent(ConsoleRE::InputEvent* const* a_event, ConsoleRE::BSTEventSource<ConsoleRE::InputEvent*>* a_source) override
		{
			if (!(*a_event))
				return ConsoleRE::BSEventNotifyControl::kContinue;

			for (ConsoleRE::InputEvent* e = *a_event; e; e = e->next)
			{
				switch (e->eventType)
				{
					// ButtonEvent
					case ConsoleRE::INPUT_EVENT_TYPE::kButton:
					{ 
						ConsoleRE::ButtonEvent* btnevent = static_cast<ConsoleRE::ButtonEvent*>(e);

						if (btnevent->value != 0 && btnevent->heldDownSecs == 0.0f)
						{
							LastControlDown = btnevent->userEvent.c_str();
							LastKeycodeDown = btnevent->idCode;
#if USE_SKSE_ADDON
							const ConsoleRE::BSFixedString& keystring = btnevent->QUserEvent();
							auto EQFOKD = SKSE::EventQueueFunctor1<uint32_t>("OnKeyDown", btnevent->idCode);
							auto EQFOCD = SKSE::EventQueueFunctor1<ConsoleRE::BSFixedString>("OnControlDown", keystring);

							SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->ForEach(btnevent->idCode, EQFOKD);
							SKSE::InputControlRegistrationMapHolder::GetSingletion()->ForEach(keystring, EQFOCD);
#endif
						}
						else if (btnevent->value == 0 && btnevent->heldDownSecs != 0.0f)
						{
							LastControlUp = btnevent->userEvent.c_str();
							LastKeycodeUp = btnevent->idCode;
#if USE_SKSE_ADDON
							const ConsoleRE::BSFixedString& keystring = btnevent->QUserEvent();
							auto EQFOKU = SKSE::EventQueueFunctor2<uint32_t, float>("OnKeyUp", btnevent->idCode, btnevent->heldDownSecs);
							auto EQFOCU = SKSE::EventQueueFunctor2<ConsoleRE::BSFixedString, float>("OnControlUp", keystring, btnevent->heldDownSecs);

							SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->ForEach(btnevent->idCode, EQFOKU);
							SKSE::InputControlRegistrationMapHolder::GetSingletion()->ForEach(keystring, EQFOCU);
#endif
						}
					}
					break;
					case ConsoleRE::INPUT_EVENT_TYPE::kThumbstick:
					{
						const ConsoleRE::ThumbstickEvent* tsevent = static_cast<const ConsoleRE::ThumbstickEvent*>(e);
						LastY = tsevent->y;
						LastX = tsevent->x;
					}
					break;
					default:
						break;
				}
			}

			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};
}