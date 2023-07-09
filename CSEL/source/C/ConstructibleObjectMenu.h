#pragma once

#include "../B/BGSConstructibleObject.h"

#include "../B/BSTArray.h"
#include "../C/CraftingSubMenu.h"
#include "../I/IMessageBoxCallback.h"

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		class ConstructibleObjectMenu : public CraftingSubMenu
		{
		public:
			class ItemEntry
			{
			public:
				BGSConstructibleObject* constructibleObject;
				uint32_t				filterFlag;
				uint32_t				Unk0C;
			};
			static_assert(sizeof(ItemEntry) == 0x10);

			class CreationConfirmCallback : public IMessageBoxCallback
			{
			public:
				~CreationConfirmCallback() override;

				// override (IMessageBoxCallback)
				void Run(uint32_t) override;
			public:
				ConstructibleObjectMenu* menu;
			};
		public:
			~ConstructibleObjectMenu() override;
			
			// override (CraftingSubMenu)
			void Accept(CallbackProcessor* a_cbReg) override;
		public:
			BSTArray<ItemEntry> unk100;
		};
	}
}