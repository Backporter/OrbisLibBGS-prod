#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../C/CraftingSubMenu.h"
#include "../I/IMessageBoxCallback.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		class AlchemyMenu : public CraftingSubMenu
		{
		public:
			class QuitMenuCallback : public IMessageBoxCallback
			{
			public:
				~QuitMenuCallback() override;

				// override (IMessageBoxCallback)
				void Run(uint32_t) override;
			public:
				AlchemyMenu* subMenu;
			};
			static_assert(sizeof(QuitMenuCallback) == 0x18);

			class UsableEffectMap
			{
			public:
				uint32_t ingredientIndex;
				uint32_t effectIndex;
				uint32_t nextCompatibleEffectMapIndex;
			};
			static_assert(sizeof(UsableEffectMap) == 0xC);

			class MenuIngredientEntry
			{
			public:
				InventoryEntryData* ingredient;
				uint8_t				effect1FilterID;
				uint8_t				effect2FilterID;
				uint8_t				effect3FilterID;
				uint8_t				effect4FilterID;
				uint8_t				isSelected;
				uint8_t				isNotGreyed;
			};
			static_assert(sizeof(MenuIngredientEntry) == 0x10);

			class CraftItemCallback : public IMessageBoxCallback
			{
			public:
				~CraftItemCallback() override;

				// override (IMessageBoxCallback)
				void Run(uint32_t) override;
			public:
				AlchemyMenu* Unk10;
				uint32_t	 Unk18;
				uint32_t	 Unk1C;
			};
			static_assert(sizeof(CraftItemCallback) == 0x20);

			class ModEffectivenessFunctor
			{
			public:
				virtual ~ModEffectivenessFunctor();

				// add
				virtual uint32_t Unk_02();
			};
		public:
			~AlchemyMenu() override;

			// override (CraftingSubMenu)
			void Accept(CallbackProcessor* a_cbReg) override;
		public:
			BSTArray<MenuIngredientEntry> ingredientsEntries;
		};
	}
}