#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"

namespace ConsoleRE
{
	class BSIMusicType;
	struct BSMusicEvent;

	class BSMusicManager : public BSTEventSink<BSMusicEvent>
	{
	public:
		~BSMusicManager() override;

		// override (BSTEventSink<BSMusicEvent>)
		BSEventNotifyControl ProcessEvent(const BSMusicEvent* a_event, BSTEventSource<BSMusicEvent>* a_eventSource) override;

		static BSMusicManager* GetSingleton()
		{
			Relocation<BSMusicManager**> singleton("", 0x30CA6D8);
			return *singleton;
		}
	public:
		BSTArray<BSIMusicType*> musicQueue;
		BSIMusicType*           current;
		uint32_t				unk30;
		uint32_t				pad34;
	};
	static_assert(sizeof(BSMusicManager) == 0x28);
}