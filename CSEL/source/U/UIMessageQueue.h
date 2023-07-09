#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTMessageQueue.h"
#include "../U/UIMessage.h"

#include "../I/IUIMessageData.h"

namespace ConsoleRE
{
	// B60
	class UIMessageQueue
	{
	public:
		UIMessageQueue();
		~UIMessageQueue();

		static UIMessageQueue* GetSingleton()
		{
			Relocation<UIMessageQueue**> Singleton("", 0x20C4308);
			return *Singleton;
		}

		void AddMessage(const BSFixedString& a_menuName, int a_type, IUIMessageData* a_data)
		{
			using func_t = void(UIMessageQueue* const, const BSFixedString&, int, IUIMessageData*);
			Relocation<func_t*> func("", 0xAC0C0);
			return func(this, a_menuName, a_type, a_data);
		}

		IUIMessageData* CreateUIMessageData(const BSFixedString& a_name)
		{
			using func_t = IUIMessageData*(UIMessageQueue* const, const BSFixedString&);
			Relocation<func_t*> func("", 0x11223F0);
			return func(this, a_name);
		}

		void ProcessCommands()
		{
			using func_t = void(UIMessageQueue* const);
			Relocation<func_t*> func("", 0x11227B0);
			return func(this);
		}
	public:
		BSTCommonStaticMessageQueue<UIMessage*, 100u> messages;
		BSTHashMap<UnkKey, UnkValue>				  Unk338;
		uint32_t									  poolUsed;
		uint32_t									  Unk35C;
		UIMessage                                     messagePool[64];
	};
}