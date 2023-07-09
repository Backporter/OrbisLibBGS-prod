#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSFixedString.h"
#include "../B/BSTEvent.h"
#include "../G/GFxValue.h"

namespace ConsoleRE
{
	class BSSaveDataEvent;
	struct BGSSaveLoadManagerEvent;

	class UISaveLoadManager : public BSTEventSink<BSSaveDataEvent>, public BSTEventSink<BGSSaveLoadManagerEvent>
	{
	public:
		~UISaveLoadManager() override;
		
		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;

		// override (BSTEventSink<BGSSaveLoadManagerEvent>)
		BSEventNotifyControl ProcessEvent(const BGSSaveLoadManagerEvent* a_event, BSTEventSource<BGSSaveLoadManagerEvent>* a_eventSource) override;

		static UISaveLoadManager* GetSingleton()
		{
			Relocation<UISaveLoadManager**> Singleton("", 0x30FDCD0);
			return *Singleton;
		}
	public:
		void*			unk18;
		uint64_t		unk20;
		BSFixedString	unk28;
		GFxValue		unk30;
		BSFixedString	unk48;
		uint64_t		unk50;
		uint64_t		unk58;
		uint64_t		unk60;
	};
	static_assert(sizeof(UISaveLoadManager) == 0x68);
}