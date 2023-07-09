#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTMessageQueue.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSThread.h"
#include "../R/RaceSexMenuEvent.h"
#include "../R/Request.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BSSaveDataEvent;
	class BGSSaveLoadManagerEvent;
	class BSSystemEvent;

	// 0x360
	class BGSSaveLoadManager : public BSTEventSink<BSSaveDataEvent>, public BSTEventSink<RaceSexMenuEvent::NameChangedEvent>, public BSTEventSource<BGSSaveLoadManagerEvent>, public BSTEventSink<BSSystemEvent>
	{
	public:
		class Thread : BSThread
		{
		public:
			~Thread() override;

			// override (BSThread)
			uint32_t	WaitForEx() override;
			void		SetEx() override;
		public:
			bool																	isRunnning;
			bool																	isBusy;
			BSEventFlag																haveTask;
			BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> asyncSaveLoadOperationQueue;
		};
	public:
		~BGSSaveLoadManager() override;

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;

		// override (BSTEventSink<RaceSexMenuEvent::NameChangedEvent>)
		BSEventNotifyControl ProcessEvent(const RaceSexMenuEvent::NameChangedEvent* a_event, BSTEventSource<RaceSexMenuEvent::NameChangedEvent>* a_eventSource) override;

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;

		static BGSSaveLoadManager* GetSingleton()
		{
			Relocation<BGSSaveLoadManager**> Singleton("", 0x313D110);
			return *Singleton;
		}

		bool Save(const char* a_fileName)
		{
			return Save_Impl(2, 0, a_fileName);
		}

		bool Load(const char* a_fileName)
		{
			return Load_Impl(a_fileName, -1, 0, true);
		}

		bool Load(const char* a_fileName, bool a_checkForMods)
		{
			return Load_Impl(a_fileName, -1, 0, a_checkForMods);
		}
	public:
		uint64_t																Unk60;
		uint64_t																Unk68;
		uint64_t																Unk70;
		uint64_t																Unk78;
		uint64_t																Unk80;
		uint64_t																Unk88;
		uint64_t																Unk90;
		uint64_t																Unk98;
		uint64_t																UnkA0;
		uint64_t																UnkA8;
		uint64_t																UnkB0;
		uint64_t																UnkB8;
		uint64_t																UnkC0;
		uint64_t																UnkC8;
		uint64_t																UnkD0;
		uint64_t																UnkD8;
		uint64_t																UnkE0;
		uint64_t																UnkE8;
		uint64_t																UnkF0;
		uint64_t																UnkF8;
		uint64_t																Unk100;
		uint64_t																Unk108;
		uint64_t																Unk110;
		uint64_t																Unk118;
		uint64_t																Unk120;
		uint64_t																Unk128;
		uint64_t																Unk130;
		uint64_t																Unk138;
		uint64_t																Unk140;
		uint64_t																Unk148;
		uint64_t																Unk150;
		uint64_t																Unk158;
		uint64_t																Unk160;
		uint64_t																Unk168;
		uint64_t																Unk170;
		uint64_t																Unk178;
		uint64_t																Unk180;
		uint64_t																Unk188;
		uint64_t																Unk190;
		uint64_t																Unk198;
		uint64_t																Unk1A0;
		uint64_t																Unk1A8;
		uint64_t																Unk1B0;
		uint64_t																Unk1B8;
		uint64_t																Unk1C0;
		uint64_t																Unk1C8;
		uint64_t																Unk1D0;
		uint64_t																Unk1D8;
		uint64_t																Unk1E0;
		uint64_t																Unk1E8;
		uint64_t																Unk1F0;
		uint64_t																Unk1F8;
		uint64_t																Unk200;
		uint64_t																Unk208;
		uint64_t																Unk210;
		uint64_t																Unk218;
		uint64_t																Unk220;
		uint64_t																Unk228;
		uint64_t																Unk230;
		uint64_t																Unk238;
		uint64_t																Unk240;
		uint64_t																Unk248;
		uint64_t																Unk250;
		uint64_t																Unk258;
		uint64_t																Unk260;
		uint64_t																Unk268;
		Thread																	Unk270;
		BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> Unk2B0;
	protected:
		bool Save_Impl(int32_t a_deviceID, uint32_t a_outputStats, const char* a_fileName);
		bool Load_Impl(const char* a_fileName, int32_t a_deviceID, uint32_t a_outputStats, bool a_checkForMods);
	};
}