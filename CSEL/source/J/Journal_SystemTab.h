#pragma once

#include "../B/BSTEvent.h"
#include "../J/JournalTab.h"

namespace ConsoleRE
{
	class BSSaveDataEvent;
	struct BGSSaveLoadManagerEvent;
	struct BSGamerProfileEvent;
	struct BSRemoteGamepadEvent;

	class Journal_SystemTab :
		public JournalTab,
		public BSTEventSink<BSSaveDataEvent>,
		public BSTEventSink<BSGamerProfileEvent>,
		public BSTEventSink<BGSSaveLoadManagerEvent>,
		public BSTEventSink<BSRemoteGamepadEvent>
	{
	public:
		~Journal_SystemTab() override;

		// override (JournalTab)
		void Accept(CallbackProcessor* a_cbReg) override;

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;

		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent* a_event, BSTEventSource<BSGamerProfileEvent>* a_eventSource) override;

		// override (BSTEventSink<BGSSaveLoadManagerEvent>)
		BSEventNotifyControl ProcessEvent(const BGSSaveLoadManagerEvent* a_event, BSTEventSource<BGSSaveLoadManagerEvent>* a_eventSource) override;

		// override (BSTEventSink<BSRemoteGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSRemoteGamepadEvent* a_event, BSTEventSource<BSRemoteGamepadEvent>* a_eventSource) override;
	};
	static_assert(sizeof(Journal_SystemTab) == 0x38);
}