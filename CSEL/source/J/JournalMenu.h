#pragma once

#include "../B/BSTEvent.h"
#include "../I/IMenu.h"
#include "../J/Journal_QuestsTab.h"
#include "../J/Journal_StatsTab.h"
#include "../J/Journal_SystemTab.h"
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class BSSystemEvent;

	class JournalMenu : public IMenu, public MenuEventHandler, public BSTEventSink<BSSystemEvent>
	{
	public:
		constexpr static inline const char* MENU_NAME = "Journal Menu";
	public:
		~JournalMenu() override;
		
		// override (IMenu)
		void     Accept(CallbackProcessor* a_processor) override;
		uint32_t ProcessMessage(UIMessage& a_message) override;
		void     AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		void     PostDisplay() override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;
	public:
		Journal_QuestsTab questsTab;
		Journal_StatsTab  statsTab;
		Journal_SystemTab systemTab;
		uint64_t		  unkD0;
		uint64_t		  unkD8;
		uint64_t		  unkE0;
	};
	static_assert(sizeof(JournalMenu) == 0xE8);
}