#pragma once

#include "../G/GPtr.h"
#include "../G/GFxValue.h"
#include "../B/BSTArray.h"
#include "../S/StandardItemData.h"
#include "../G/GFxMovieRoot.h"
#include "../P/PlayerCharacter.h"

namespace ConsoleRE
{
	class Item;

	class ItemList
	{
	public:
		class Item
		{
		public:
			StandardItemData data;
			GFxValue obj;
		};
		
		Item*	GetSelectedItem()
		{
			if (unk50)
				return nullptr;

			GFxValue selectedIndex;
			auto     success = root.GetMember("selectedIndex", &selectedIndex);
			if (!success || !selectedIndex.GetType() == GFxValue::ValueType_Double) 
			{
				return nullptr;
			}


			auto idx = static_cast<int32_t>(selectedIndex.GetValueDouble());
			if (idx < 0 || static_cast<size_t>(idx) >= items.Count) 
			{
				return nullptr;
			}

			return items.Entries[idx];
		}

		void	Update()
		{
			Update(PlayerCharacter::GetSingleton());
		}

		void Update(TESObjectREFR* a_owner)
		{
			typedef void(*_FN)(void*, TESObjectREFR*);
			Relocation<_FN> FN("", 0xA23580);
			return FN(this, a_owner);
		}

	public:
		GPtr<GFxMovieView> view;       // 00
		GFxValue           root;       // 08 - kDisplayObject - "_level0.Menu_mc.inventoryLists.panelContainer.itemList"
		GFxValue           entryList;  // 20 - kArray - root.GetMember("entryList", &entryList);
		BSTArray<Item*>    items;      // 38
		bool               unk50;      // 50
		uint8_t			   pad51;      // 51
		uint16_t		   pad52;      // 52
		uint32_t		   pad54;      // 54
	};
}