#pragma once

#include "../B/BSTEvent.h"
#include "../G/GFxFunctionHandler.h"
#include "../I/IMenu.h"
#include "../I/ImageData.h"

namespace ConsoleRE
{
	class BSSaveDataEvent;
	class BSSystemEvent;
	class BSGamerProfileEvent;

	class MainMenu :
		public IMenu,
		public BSTEventSink<BSSystemEvent>,
		public BSTEventSink<BSSaveDataEvent>,
		public BSTEventSink<BSGamerProfileEvent>,
		public GFxFunctionHandler
	{
	public:
		constexpr static inline const char* MENU_NAME = "Main Menu";
	public:
		~MainMenu() override;

		// override (IMenu)
		void     Accept(CallbackProcessor* a_processor) override;
		uint32_t ProcessMessage(UIMessage& a_message) override;
		void     AdvanceMovie(float a_interval, uint32_t a_currentTime) override;

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;

		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent* a_event, BSTEventSource<BSGamerProfileEvent>* a_eventSource) override;

		 // override (GFxFunctionHandler)
		void Call(Params& a_params) override;
	public:
		ImageData   unk50;
		uint32_t	unk68;
		uint8_t		unk6C;
		uint8_t		unk6D;
		uint8_t		unk6E;
		uint8_t		pad6F;
	};
	static_assert(sizeof(MainMenu) == 0x78);
}