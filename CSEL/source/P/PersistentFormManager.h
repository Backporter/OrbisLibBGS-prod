#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSTArray.h"
#include "../E/EnchantmentItem.h"
#include "../M/MagicItem.h"
#include "../E/Effect.h"

namespace ConsoleRE
{
	class PersistentFormManager
	{
	public:
		struct EnchantmentEntry
		{
		public:
			EnchantmentItem*       enchantment;
			volatile uint32_t	   referenceCount;
			uint32_t			   paddingC;
		};
		static_assert(sizeof(EnchantmentEntry) == 0x10, "");
	public:
		PersistentFormManager() = delete;
		~PersistentFormManager() = delete;

		static PersistentFormManager* GetSingleton()
		{
			Relocation<PersistentFormManager**> Singleton("", 0x20BFF80);
			return *Singleton;
		}

		void			  CreatePotion(AlchemyItem*& a_ret, BSTArray<Effect>& a_effectarr)
		{
			using func_t = void(decltype(this), AlchemyItem*&, BSTArray<Effect>&);
			Relocation<func_t*> func("", 0x692280);
			return func(this, a_ret, a_effectarr);
		}

		void			  CreatePoison(BSTArray<Effect>& a_array, AlchemyItem*& a_poison)
		{
			using func_t = void(decltype(this), BSTArray<Effect>&, AlchemyItem*&);
			Relocation<func_t*> func("", 0x6923D0);
			return func(this, a_array, a_poison);
		}

		EnchantmentItem*  CreateOffensiveEnchantment(BSTArray<Effect>& a_array)
		{				  
			using func_t  = EnchantmentItem*(decltype(this), BSTArray<Effect>&);
			Relocation<func_t*> func("", 0x691FD0);
			return func(this, a_array);
		}				  
						  
		EnchantmentItem*  CreateDefensiveEnchantment(BSTArray<Effect>& a_array)
		{
			using func_t = EnchantmentItem*(decltype(this), BSTArray<Effect>&);
			Relocation<func_t*> func("", 0x692130);
			return func(this, a_array);
		}

		void			  ScheduleForDeletion(TESForm* a_form)
		{
			using func_t = void(decltype(this), TESForm*);
			Relocation<func_t*> func("", 0x6929C0);
			return func(this, a_form);
		}

		void			 IncrementEnchantmentReferenceCount(EnchantmentItem* a_enchantment, volatile int32_t a_decrementValue = 1)
		{
			if (a_enchantment && a_enchantment->FormID >= 0xFF000000)
			{
				for (auto& enchmentdata : weaponEnchantments)
				{
					if (enchmentdata.enchantment == a_enchantment)
					{
						__sync_add_and_fetch(&enchmentdata.referenceCount, a_decrementValue);
						break;
					}
				}

				for (auto& enchmentdata : armorEnchantments)
				{
					if (enchmentdata.enchantment == a_enchantment)
					{
						__sync_add_and_fetch(&enchmentdata.referenceCount, a_decrementValue);
						break;
					}
				}

			}
		}

		void			 DecrementEnchantmentReferenceCount(EnchantmentItem* a_enchantment, volatile int32_t a_decrementValue = 1)
		{
			if (a_enchantment && a_enchantment->FormID >= 0xFF000000)
			{
				for (auto& enchmentdata : weaponEnchantments)
				{
					if (enchmentdata.enchantment == a_enchantment)
					{
						if (!__sync_sub_and_fetch(&enchmentdata.referenceCount, a_decrementValue))
							ScheduleForDeletion(a_enchantment);

						break;
					}
				}

				for (auto& enchmentdata : armorEnchantments)
				{
					if (enchmentdata.enchantment == a_enchantment)
					{
						if (!__sync_sub_and_fetch(&enchmentdata.referenceCount, a_decrementValue))
							ScheduleForDeletion(a_enchantment);
						
						break;
					}
				}

			}
		}
	public:
		BSTArray<EnchantmentEntry> weaponEnchantments;
		BSTArray<EnchantmentEntry> armorEnchantments;
	};
}