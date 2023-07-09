#pragma once

#include "../B/BSTEvent.h"
#include "../F/FxDelegateHandler.h"
#include "../G/GFxValue.h"

#include "../G/GFxMovieRoot.h"

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		struct TESFurnitureEvent;
			
		class CraftingSubMenu : public FxDelegateHandler, public BSTEventSink<TESFurnitureEvent>
		{
		public:
			~CraftingSubMenu() override;

			// add
			virtual void Unk_02(void);
			virtual void Unk_03(void);
			virtual void Unk_04(void);
			virtual void Unk_05(void);
			virtual void Unk_06(void);

			// override (BSTEventSink<TESFurnitureEvent>)
			BSEventNotifyControl ProcessEvent(const TESFurnitureEvent*, BSTEventSource<TESFurnitureEvent>*);

			// add
			virtual void Unk_07(void);
		public:
			GFxMovieRoot*	movie;
			TESFurniture*	furniture;
			void*			Unk28;
			GFxValue*		Unk30;
			GFxValue		Unk38;
			GFxValue		Unk50;
			GFxValue		Unk68;
			GFxValue		Unk80;
			GFxValue		Unk98;
			GFxValue		UnkB0;
			GFxValue		UnkC8;
			GFxValue		UnkE0;
			uint64_t		UnkF8;
		};
		static_assert(offsetof(CraftingSubMenu, movie) == 0x18);
		static_assert(sizeof(CraftingSubMenu) == 0x100);
	}
}