#pragma once

#include "../C/CraftingSubMenu.h"
#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		// 0x200
		class EnchantConstructMenu : public CraftingSubMenus::CraftingSubMenu
		{
		public:
			// is this CategoryListEntry but renamed?, why would both exist on PC? but only one on console? did clang combine the two?
			class EnchantMenuCallback : public BSIntrusiveRefCounted
			{
			public:
				enum FilterFlag : uint32_t
				{
					kNone = 0,
					kEnchantWeapon = 1U << 0,
					kDisenchantWeapon = 1U << 1,
					kEnchantArmor = 1U << 2,
					kDisenchantArmor = 1U << 3,
					kEffectWeapon = 1U << 4,
					kEffectArmor = 1U << 5,
					kSoulGem = 1U << 6
				};
			public:
				virtual ~EnchantMenuCallback();
				virtual void Run(uint32_t) = 0;
			public:
				uint32_t Flag;
				uint8_t  bEquipped;
				uint8_t	 BEnabled;
				uint16_t Unk12;
				uint32_t Unk14;
			};
			static_assert(sizeof(EnchantMenuCallback) == 0x18, "EnchantConstructMenu::EnchantMenuCallback");

			class CreateEffectFunctor : public EnchantMenuCallback
			{
			public:
				virtual ~CreateEffectFunctor();
				virtual void Run(uint32_t) override;
			};

			// 0x20
			class ItemChangeEntry : public EnchantMenuCallback
			{
			public:
				virtual ~ItemChangeEntry();
				virtual void Run(uint32_t) override;
			public:
				InventoryEntryData* inventoryEntryData;
			};

			class EnchantmentEntry : public EnchantMenuCallback
			{
			public:
				virtual ~EnchantmentEntry();
				virtual void Run(uint32_t) override;
			};

			class EnchantMenuDisenchantCallback : public EnchantMenuCallback
			{
			public:
				virtual ~EnchantMenuDisenchantCallback();
				virtual void Run(uint32_t) override;
			};

			class EnchantMenuExitCallback : public EnchantMenuCallback
			{
			public:
				virtual ~EnchantMenuExitCallback();
				virtual void Run(uint32_t a_msg) override;
			};

			class EnchantMenuCraftCallback : public EnchantMenuCallback
			{
			public:
				virtual ~EnchantMenuCraftCallback();
				virtual void Run(uint32_t) override;
			};
		public:
			EnchantConstructMenu();
			virtual ~EnchantConstructMenu();
		public:
		};
	}
}