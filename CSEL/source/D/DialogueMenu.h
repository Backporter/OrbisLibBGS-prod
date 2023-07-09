#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class MenuOpenCloseEvent;

	class DialogueMenu : public IMenu, public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		constexpr static inline const char* MENU_NAME = "Dialogue Menu";
	
		struct Data
		{
			void*       unk00;
			uint64_t	unk08;
		};
		static_assert(sizeof(Data) == 0x10);
	public:
		~DialogueMenu() override;

		// override (IMenu)
		void     Accept(CallbackProcessor* a_processor) override;
		uint32_t ProcessMessage(UIMessage& a_message) override;

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;
	public:
		BSTArray<Data> unk38;
	};
	static_assert(sizeof(DialogueMenu) == 0x48);
}