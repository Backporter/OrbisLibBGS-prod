#include "../../../../../OrbisUtil/include/Relocation.h"

#include "../../../../Build/Flags.h"
#include "../../../../source/S/StandardItemData.h"
#include "../../../../source/T/TESForm.h"
#include "../../../../source/T/TESObjectARMO.h"
#include "../../../../source/T/TESAmmo.h"
#include "../../../../source/T/TESObjectWEAP.h"
#include "../../../../source/T/TESSoulGem.h"
#include "../../../../source/A/AlchemyItem.h"
#include "../../../../source/T/TESObjectBOOK.h"
#include "../../../../source/G/GFxMovieView.h"
#include "../../../../source/P/PlayerCharacter.h"
#include "../../../../source/B/BGSKeyword.h"
#include "../../../../source/M/MagicItemData.h"
#include "../../../../source/T/TESShout.h"
#include "../../../../source/E/EffectSetting.h"
#include "../../../../source/I/IngredientItem.h"
#include "../../../../source/S/ScrollItem.h"
#include "../../../../source/E/Effect.h"
#include "../../../../source/B/BGSEquipSlot.h"
#include "../../../../source/T/TESWordOfPower.h"
#include "../../../../source/T/TESRace.h"


#include "../../../../source/RTTI.h"

#include "ItemData.h"
#include "../CraftingSubMenus/InventoryPlugin.h"

#include <stdint.h>
#include <math.h>
#include <cmath>

namespace ItemData
{
	using namespace ConsoleRE;

	bool Extend = false;
	bool ExtendAlchemyCategories = false;

	typedef void(*StandardItemData_ctor)(ConsoleRE::StandardItemData* a_this, ConsoleRE::GFxMovieView** movie, void*, void*);
	typedef void(*MagicItemData_ctor)(ConsoleRE::MagicItemData* a_this, ConsoleRE::GFxMovieView** movie, ConsoleRE::TESForm* Unk3, int Unk4);

	Relocation<StandardItemData_ctor> StandardItemDataCtor("StandardItemData:ctor", 0x9DC710);
	Relocation<MagicItemData_ctor> MagicItemDataCtor("MagicItemData:ctor", 0xA3A030);

	class BGSListFormVisitor
	{
	public:
		BGSListFormVisitor(GFxValue* a_array, GFxMovieView* a_movie) : m_array(a_array), m_movie(a_movie)
		{

		}

		~BGSListFormVisitor()
		{

		}

		bool Accept(TESForm* form)
		{
			if (form)
			{
				GFxValue obj;
				m_movie->CreateObject(&obj);

				ItemData::common(&obj, m_movie, form);
				ItemData::ListForm(&obj, m_movie, form);
				m_array->PushBack(obj);
				
			}

			return false;
		}
	public:
		GFxValue*     m_array;
		GFxMovieView* m_movie;
	};

	void common(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form)
	{
		if (!gfxv || !form || !gfxv->IsObject())
			return;

		gfxv->RegisterNumber("formType", form->FormType);
		gfxv->RegisterNumber("formId",   form->FormID);
	}

	void Standard(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form, InventoryEntryData* Unk3)
	{
		if (!gfxv || !form || !gfxv->IsObject())
			return;

		switch (form->FormType)
		{
		case ConsoleRE::TESObjectARMO::TypeID:
		{
			TESObjectARMO* f = TES_RTTI(form, TESForm, TESObjectARMO);
			if (f)
			{
				gfxv->RegisterNumber("partMask", f->GetSlotMask());
				gfxv->RegisterNumber("weightClass", f->GetArmorType());
			}
		}
		break;
		case ConsoleRE::TESAmmo::TypeID:
		{
			ConsoleRE::TESAmmo* f = TES_RTTI(form, TESForm, TESAmmo);
			if (f)
			{
				gfxv->RegisterNumber("flags", f->data.flags);
			}
		}
		break;
		case ConsoleRE::TESObjectWEAP::TypeID:
		{
			ConsoleRE::TESObjectWEAP* f = TES_RTTI(form, TESForm, TESObjectWEAP);
			if (f)
			{
				gfxv->RegisterNumber("weaponType",	f->weaponData.animationType);
				gfxv->RegisterNumber("speed",		f->weaponData.speed);
				gfxv->RegisterNumber("reach",		f->weaponData.reach);
				gfxv->RegisterNumber("stagger",		f->weaponData.staggerValue);
				gfxv->RegisterNumber("critDamage",	f->criticalData.damage);
				gfxv->RegisterNumber("minRange",	f->weaponData.minRange);
				gfxv->RegisterNumber("maxRange",	f->weaponData.maxRange);
				gfxv->RegisterNumber("baseDamage",	f->attackDamage);

				if (f->equipSlot)
					gfxv->RegisterNumber("equipSlot", f->equipSlot->FormID);

			}
		}
		break;
		case ConsoleRE::TESSoulGem::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, TESSoulGem);
			if (f)
			{
				gfxv->RegisterNumber("gemSize", f->GetMaximumCapacity());
				gfxv->RegisterNumber("soulSize", (Unk3 ? Unk3->GetSoulLevel() : f->GetContainedSoul()));
			}
		}
		break;
		case ConsoleRE::AlchemyItem::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, AlchemyItem);
			if (f)
			{
				gfxv->RegisterNumber("flags", f->data.flags);
			}

		}
		break;
		case ConsoleRE::TESObjectBOOK::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, TESObjectBOOK);
			if (f)
			{
				gfxv->RegisterNumber("flags", f->data.flags);
				gfxv->RegisterNumber("bookType", f->data.type);

				switch (f->data.GetSanitizedType())
				{
				case 1:
					gfxv->RegisterNumber("teachesSkill", f->data.teaches.actorValueToAdvance);
					break;
				case 4:
					gfxv->RegisterNumber("teachesSpell", f->data.teaches.spell ? f->data.teaches.spell->FormID : -1);
					break;
				}
			}
		}
		break;
		default:
			break;
		}
	}

	void iteminfo(ConsoleRE::GFxValue* gfxv, InventoryEntryData* ptr)
	{
		if (!gfxv || !ptr || !gfxv->IsObject())
			return;

		gfxv->RegisterNumber("value", ptr->GetValue());
		gfxv->RegisterNumber("weight", ptr->GetWeight());
		gfxv->RegisterNumber("isStolen", !ptr->IsOwnedBy(PlayerCharacter::GetSingleton()));
	}

	void inv(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form, void* Unk3)
	{
		if (!gfxv || !movie || !form || !gfxv->IsObject())
			return;

		GFxValue keywordtoo;
		movie->CreateObject(&keywordtoo);

		auto keywords = TES_RTTI(form, TESForm, BGSKeywordForm);
		if (keywords)
		{
			if (keywords->keywords)
			{
				for (int i = 0; i < keywords->numKeywords; i++)
				{
					auto key = keywords->keywords[i];
					if (key)
					{
						auto str = key->keyword.c_str();
						if (str)
						{
							keywordtoo.RegisterBool(str, true);
						}
					}
				}
			}
		}

		gfxv->SetMember("keywords", &keywordtoo);


		switch (form->FormType)
		{
		case ConsoleRE::TESObjectARMO::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, TESObjectARMO);
			if (f)
			{
				auto val = (Unk3 ? ConsoleRE::PlayerCharacter::GetSingleton()->GetArmorValue((InventoryEntryData*)Unk3) : 0);
				val = std::round(val);
				gfxv->RegisterNumber("armor", val);
			}
		}
		break;
		case ConsoleRE::TESObjectWEAP::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, TESObjectWEAP);
			if (f)
			{
				auto val = (Unk3 ? ConsoleRE::PlayerCharacter::GetSingleton()->GetDamage((InventoryEntryData*)Unk3) : 0);
				val = std::round(val);
				gfxv->RegisterNumber("damage", val);
			}
		}
		break;
		case ConsoleRE::TESAmmo::TypeID:
		{
			auto f = TES_RTTI(form, TESForm, TESAmmo);
			if (f)
			{
				auto val = (Unk3 ? ConsoleRE::PlayerCharacter::GetSingleton()->GetDamage((InventoryEntryData*)Unk3) : 0);
				val = std::round(val);
				gfxv->RegisterNumber("damage", val);
			}
		}
		break;
		default:
			break;
		}
	}

	void magic(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form)
	{
		if (!gfxv || !movie || !form || !gfxv->IsObject())
			return;

		switch (form->FormType)
		{
			// magic based items
			case SpellItem::TypeID:
			case ScrollItem::TypeID:
			case IngredientItem::TypeID:
			case AlchemyItem::TypeID:
			case EnchantmentItem::TypeID:
			{
				MagicItem* f = TES_RTTI(form, TESForm, MagicItem);
				if (f)
				{
					if (f->name.c_str())
					{
						gfxv->RegisterString("spellName", f->name.c_str());
					}

					Effect* effect = f->GetCostliestEffectItem(5, false);
					if (effect && effect->baseEffect)
					{
						gfxv->RegisterNumber("magnitude", effect->GetMagnitude());
						gfxv->RegisterNumber("duration", effect->GetDuration());
						gfxv->RegisterNumber("area", effect->GetArea());
						magic(gfxv, movie, effect->baseEffect);
					}
				}

				SpellItem* spellitem = TES_RTTI(form, MagicItem, SpellItem);
				if (spellitem)
				{
					gfxv->RegisterNumber("spellitem", spellitem->spellType);
					gfxv->RegisterNumber("trueCost", spellitem->costOverride);

					if (spellitem->equipSlot)
					{ 
						gfxv->RegisterNumber("equipSlot", spellitem->equipSlot->FormID);
					}
				}

				AlchemyItem* alchemyitem = TES_RTTI(form, MagicItem, AlchemyItem);
				if (alchemyitem)
				{
					if (alchemyitem->data.consumptionSound)
					{
						GFxValue use;
						movie->CreateObject(&use);
						
						ItemData::common(&use, movie, alchemyitem->data.consumptionSound);
						ItemData::ListForm(gfxv, movie, alchemyitem->data.consumptionSound);
						gfxv->SetMember("useSound", &use);
					}
				}

				EnchantmentItem * enchantmentItem = TES_RTTI(form, MagicItem, EnchantmentItem);
				if (enchantmentItem)
				{
					gfxv->RegisterNumber("flags", enchantmentItem->data.flags);
					GFxValue baseEnchant;
					movie->CreateObject(&baseEnchant);
					common(&baseEnchant, movie, enchantmentItem->data.baseEnchantment);
					ListForm(&baseEnchant, movie, enchantmentItem->data.baseEnchantment);
					gfxv->SetMember("baseEnchant", &baseEnchant);
					
					GFxValue restrictions;
					movie->CreateObject(&restrictions);
					common(&restrictions, movie, enchantmentItem->data.wornRestrictions);
					ListForm(&restrictions, movie, enchantmentItem->data.wornRestrictions);
					gfxv->SetMember("restrictions", &restrictions);
				}
			}
			break;
			case EffectSetting::TypeID:
			{
				auto f = TES_RTTI(form, TESForm, EffectSetting);
				if (f)
				{
					if (f->name.c_str())
					{
						gfxv->RegisterString("effectName", f->name.c_str());
					}
					
					gfxv->RegisterNumber("subType",		 f->data.associatedSkill);
					gfxv->RegisterNumber("effectFlags",  f->data.flags);
					gfxv->RegisterNumber("school",		 f->data.associatedSkill);
					gfxv->RegisterNumber("skillLevel",	 f->data.minimumSkill);
					gfxv->RegisterNumber("archetype",	 f->data.archetype);
					gfxv->RegisterNumber("deliveryType", f->data.delivery);
					gfxv->RegisterNumber("castTime",	 f->data.spellmakingChargeTime);
					gfxv->RegisterNumber("delayTime",	 f->data.aiDelayTimer);
					gfxv->RegisterNumber("actorValue",	 f->data.primaryAV);
					gfxv->RegisterNumber("castType",	 f->data.castingType);
					gfxv->RegisterNumber("magicType",	 f->data.resistVariable);
				}
			}
			break;
			case TESShout::TypeID:
			{
				auto f = TES_RTTI(form, TESForm, TESShout);
				if (f)
				{
					if (f->name.c_str())
					{
						gfxv->RegisterString("fullName", f->name.c_str());
					}
			
					GFxValue wordarray;
					movie->CreateArray(&wordarray);
					for (int i = 0; i < 3; i++)
					{
						GFxValue word;
						movie->CreateObject(&word);
					
						if (f->words[i].word && f->words[i].word->name.c_str())
							word.RegisterString("word", f->words[i].word->name.c_str());
					
						if (f->words[i].word && f->words[i].word->translation.c_str())
							word.RegisterString("fullName", f->words[i].word->translation.c_str());
					
						word.RegisterNumber("recoveryTime", f->words[i].recoveryTime);
						
						ItemData::common(&word, movie, f->words[i].spell);
						ItemData::ListForm(&word, movie, f->words[i].spell);
						wordarray.PushBack(word);
					}
			
					gfxv->SetMember("words", &wordarray);
				}
			}
			break;
			default:
			break;
		}
	}

	void ListForm(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form)
	{
		if (!gfxv || !movie || !form || !gfxv->IsObject())
			return;

		if (form->FormType == ConsoleRE::BGSListForm::TypeID)
		{
			BGSListForm* ListForm = TES_RTTI(form, TESForm, BGSListForm);
			if (ListForm)
			{
				GFxValue Array;
				movie->CreateArray(&Array);
				BGSListFormVisitor vis(&Array, movie);
				ListForm->Visit(vis);

				gfxv->SetMember("forms", &Array);
			}
		}
	}

	void actor(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, TESForm* form)
	{
		if (!gfxv || !movie || !form || !gfxv->IsObject())
			return;

		switch (form->FormType)
		{
			case ConsoleRE::TESRace::TypeID:
			{
				TESRace* race = TES_RTTI(form, TESForm, TESRace);
				if (race)
				{
					if (race->name.c_str())
						gfxv->RegisterString("fullName", race->name.c_str());

					if (race->formEditorID.c_str())
						gfxv->RegisterString("editorId", race->name.c_str());

					/* */
					GFxValue spells;
					movie->CreateArray(&spells);

					for (int i = 0; i < race->GetSpellCount(); i++)
					{
						GFxValue spell;
						movie->CreateObject(&spell);
						
						TESForm* form = race->GetSpell(i);
						ItemData::common(&spell, movie, form);
						ItemData::ListForm(&spell, movie, form);
						spells.PushBack(spell);
					}
					gfxv->SetMember("spells", &spells);

					/* */
					GFxValue shouts;
					movie->CreateArray(&shouts);

					for (int i = 0; i < race->GetShoutCount(); i++)
					{
						GFxValue shout;
						movie->CreateObject(&shout);

						TESForm* form = race->GetShout(i);
						ItemData::common(&shout, movie, form);
						ItemData::ListForm(&shout, movie, form);
						
						shouts.PushBack(shout);
					}
					gfxv->SetMember("shouts", &shouts);

					/* */
					GFxValue bonuses;
					movie->CreateArray(&bonuses);

					for (int i = 0; i < 7; i++)
					{
						GFxValue skillBonus;
						movie->CreateObject(&skillBonus);

						skillBonus.RegisterNumber("skill", race->data.bonuses[i].skill);
						skillBonus.RegisterNumber("bonus", race->data.bonuses[i].bonus);
						bonuses.PushBack(skillBonus);
					}

					gfxv->SetMember("skillBonuses", &bonuses);
				}
			}
			break;
			case ConsoleRE::TESNPC::TypeID:
			{
				TESNPC* npc = TES_RTTI(form, TESForm, TESNPC);
				if (npc)
				{
					if (static_cast<TESFullName*>(npc)->name.c_str())
						gfxv->RegisterString("fullName", static_cast<TESFullName*>(npc)->name.c_str());

					if (npc->shortName.c_str())
						gfxv->RegisterString("shortName", npc->shortName.c_str());

					gfxv->RegisterNumber("weight", npc->weight);

					if ((static_cast<TESActorBaseData*>(npc)->actorData.actorBaseFlags & 128) == 128)
						gfxv->RegisterNumber("levelMult", static_cast<double>(static_cast<TESActorBaseData*>(npc)->actorData.level / 1000.0));
					else
						gfxv->RegisterNumber("level", static_cast<double>(static_cast<TESActorBaseData*>(npc)->actorData.level));

					gfxv->RegisterNumber("minLevel", static_cast<double>(static_cast<TESActorBaseData*>(npc)->actorData.calcLevelMin));
					gfxv->RegisterNumber("maxLevel", static_cast<double>(static_cast<TESActorBaseData*>(npc)->actorData.calcLevelMax));

					/* */
					GFxValue race;
					movie->CreateObject(&race);
					ItemData::common  (&race, movie, static_cast<TESRaceForm*>(npc)->race);
					ItemData::ListForm(&race, movie, static_cast<TESRaceForm*>(npc)->race);
					gfxv->SetMember("race", &race);

					/* */
					GFxValue spells;
					movie->CreateArray(&spells);
					for (int i = 0; i < static_cast<TESSpellList*>(npc)->GetSpellCount(); i++)
					{
						GFxValue spell;
						movie->CreateObject(&spell);

						ItemData::common(&spell, movie, static_cast<TESSpellList*>(npc)->GetSpell(i));
						ItemData::ListForm(&spell, movie, static_cast<TESSpellList*>(npc)->GetSpell(i));

						spells.PushBack(spell);
					}
					gfxv->SetMember("spells", &spells);

					/* */
					GFxValue shouts;
					movie->CreateArray(&shouts);
					for (int i = 0; i < static_cast<TESSpellList*>(npc)->GetShoutCount(); i++)
					{
						GFxValue shout;
						movie->CreateObject(&shout);
						ItemData::common(&shout, movie, static_cast<TESSpellList*>(npc)->GetShout(i));
						ItemData::ListForm(&shout, movie, static_cast<TESSpellList*>(npc)->GetShout(i));
						shouts.PushBack(shout);
					}
					gfxv->SetMember("shouts", &shouts);
				}
			}
			break;
		 // case ConsoleRE::Character::TypeID:
			case ConsoleRE::PlayerCharacter::TypeID:
			{
				ConsoleRE::Actor* actor = TES_RTTI(form, TESForm, Actor);
				if (actor)
				{
					/* */
					GFxValue actorBase;
					movie->CreateObject(&actorBase);
					ItemData::common(&actorBase, movie, actor->data.objectReference);
					ItemData::ListForm(&actorBase, movie, actor->data.objectReference);
					gfxv->SetMember("actorBase", &actorBase);
					gfxv->RegisterString("fullName", actor->GetDisplayFullName());
				
					/* */
					GFxValue addedSpells;
					movie->CreateArray(&addedSpells);
					for (int i = 0; i < actor->addedSpells.size(); i++)
					{
						GFxValue spell;
						movie->CreateObject(&spell);
						ItemData::common(&spell, movie,   actor->addedSpells[i]);
						ItemData::ListForm(&spell, movie, actor->addedSpells[i]);	
						addedSpells.PushBack(spell);
					}
					gfxv->SetMember("spells", &addedSpells);


					// experimental.
					GFxValue activeEffects;
					movie->CreateArray(&activeEffects);

					BSSimpleList<ActiveEffect*>* effects = actor->GetActiveEffectList();
					if (effects)
					{
						for (int i = 0; i < effects->Count(); i++)
						{
							GFxValue effect;
							movie->CreateObject(&effect);

							PRINT_POS;
							ActiveEffect * pEffect = effects->GetItem(i);
							PRINT_POS;

							if (pEffect->spell)
								magic(&effect, movie, static_cast<TESForm*>(pEffect->spell));

							effect.RegisterNumber("elapsed",   pEffect->elapsedSeconds);
							effect.RegisterNumber("duration",  pEffect->duration);
							effect.RegisterNumber("magnitude", pEffect->magnitude);
							effect.RegisterBool("inactive", (pEffect->flags & 0x8000) == 0x8000);

							// ActiveEffect
							if (pEffect->effect && pEffect->effect->baseEffect)
								magic(&effect, movie, pEffect->effect->baseEffect);

							activeEffects.PushBack(effect);
						}
					}
					gfxv->SetMember("activeEffects", &activeEffects);


					/* */

					GFxValue actorValues;
					movie->CreateArray(&actorValues);

					for (int i = 0; i < 164; i++)
					{
						GFxValue actorValue;
						movie->CreateObject(&actorValue);

						actorValue.RegisterNumber("current", actor->GetActorValue(i));
						actorValue.RegisterNumber("maximum", actor->GetPermanentActorValue(i));
						actorValue.RegisterNumber("base",    actor->GetBaseActorValue(i));

						actorValues.PushBack(actorValue);
					}

					gfxv->SetMember("actorValues", &actorValues);
				}

				PlayerCharacter* player = TES_RTTI(form, TESForm, PlayerCharacter);
				if (player)
				{
					gfxv->RegisterNumber("perkPoints", player->UnkA31);

				}
			}
			break;
			default:
			break;
		}
	}


	void form(ConsoleRE::GFxValue* a_gfxv, ConsoleRE::GFxMovieView* a_movie, ConsoleRE::TESForm* a_form)
	{
		if (!a_gfxv || !a_form || !a_gfxv->IsObject())
			return;

		common(a_gfxv, a_movie, a_form);
		ListForm(a_gfxv, a_movie, a_form);
	}

	void StandardItemDataHook(ConsoleRE::StandardItemData* a_this, ConsoleRE::GFxMovieView** movie, void* Unk3, void* Unk4)
	{
		StandardItemDataCtor(a_this, movie, Unk3, Unk4);
		if (Extend)
		{
			auto* f = static_cast<InventoryEntryData*>(Unk3);
			common(&a_this->Unk18,   *movie, f->form);
			Standard(&a_this->Unk18, *movie, f->form, f);
			inv(&a_this->Unk18,      *movie, f->form, Unk3);
			magic(&a_this->Unk18, *movie, f->form);

			auto pluginList = InventoryPlugin::getPluginList();
			for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
				if (*iter)
					(*iter)(*movie, &a_this->Unk18, f);
		}
	}
	
	void MagicItemDataHook(ConsoleRE::MagicItemData* a_this, ConsoleRE::GFxMovieView** movie, ConsoleRE::TESForm* Unk3, int Unk4)
	{
		MagicItemDataCtor(a_this, movie, Unk3, Unk4);

		if (Extend)
		{
			common(&a_this->Unk20, *movie, Unk3);
			magic(&a_this->Unk20, *movie, Unk3);
		}
	}
}