#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class ActorValueMeter;
	class HUDObject;
	class ShoutMeter;
	class UserEventEnabledEvent;
	struct BSRemoteGamepadEvent;

	class HUDMenu : public IMenu, public BSTEventSink<UserEventEnabledEvent>, public BSTEventSink<BSRemoteGamepadEvent>
	{
	public:
		constexpr static const char* MENU_NAME = "HUD Menu";
	public:
		~HUDMenu() override;
		
		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;
		uint32_t		   ProcessMessage(UIMessage& a_message) override;
		void               AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		void               RefreshPlatform() override;

		// override (BSTEventSink<UserEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent* a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource) override;
		
		// override (BSTEventSink<BSRemoteGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSRemoteGamepadEvent* a_event, BSTEventSource<BSRemoteGamepadEvent>* a_eventSource) override;
	public:
		BSTArray<HUDObject*> objects;
		ActorValueMeter*     health;
		ActorValueMeter*     stamina;
		ActorValueMeter*     magicka;
		ShoutMeter*          shout;
		GFxValue             root;
		uint64_t			 unk90;
	};
	static_assert(sizeof(HUDMenu) == 0x90);
}