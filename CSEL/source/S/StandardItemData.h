#pragma once

#include <stdint.h>

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSTList.h"
#include "../G/GFxValue.h"
#include "../T/TESBoundObject.h"
#include "../E/ExtraDataList.h"

namespace ConsoleRE
{
	class ExtraDataList;

	class StandardItemData
	{
	public:
		// 0x9DC710
		StandardItemData();
		virtual ~StandardItemData();

		virtual const char* Unk_02();
		virtual uint32_t    Unk_03();
		virtual uint32_t    Unk_04();
		virtual uint32_t    Unk_05();
		virtual uint32_t    Unk_06();
		virtual bool        Unk_07();

		static size_t GetStandardItemDataSize() { return sizeof(StandardItemData); }
	public:
		struct ItemData
		{
		public:
			bool IsQuestObject()
			{
				typedef bool(*_FN)(decltype(this));
				Relocation<_FN> FN("", 0x134FB0);
				return FN(this);
			}
		public:
			TESBoundObject*               object{ nullptr };      // 00
			BSSimpleList<ExtraDataList*>* extraLists{ nullptr };  // 08
			int32_t                       countDelta{ 0 };        // 10
			uint32_t                      pad14{ 0 };             // 14
		};

		ItemData*   Unk08;
		void*		Unk10;
		GFxValue	Unk18;
		uint8_t		Unk30[0x10];
	};
	static_assert(offsetof(StandardItemData, Unk18) == 0x18, "#");
	static_assert(sizeof(StandardItemData) == 0x40, "#");
}