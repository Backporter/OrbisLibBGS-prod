#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../A/Actor.h"
#include "../T/TESForm.h"
#include "../E/ExtraDataList.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BGSEquipmentManger
	{
	public:
		BGSEquipmentManger();
		~BGSEquipmentManger();
		
		static BGSEquipmentManger* GetSingleton() 
		{
			Relocation<BGSEquipmentManger**> singleton("", 0x30C77A8);
			return *singleton;
		}

		void EquipItem(Actor* a_actor, TESForm* a_form, BaseExtraList* a_extraList, int32_t a_count, BGSEquipSlot* a_slot, bool a_buseSound, bool a_userlock, bool a_showEquiped, void* a_unk1)
		{
			using func_t = void(decltype(this), Actor*, TESForm*, BaseExtraList*, int32_t, BGSEquipSlot* , bool, bool, bool, void*);
			Relocation<func_t*> func("", 0x754F40);
			return func(this, a_actor, a_form, a_extraList, a_count, a_slot, a_buseSound, a_userlock, a_showEquiped, a_unk1);
		}

		void UnequipItem(Actor* a_actor, TESForm* a_form, BaseExtraList* a_extraList, int32_t a_count, BGSEquipSlot* a_slot, bool a_unk1, bool a_equipLock, bool a_unk2, bool a_unk3, void* a_unk4)
		{
			using func_t = void(decltype(this), Actor* , TESForm* , BaseExtraList*, int32_t, BGSEquipSlot* , bool, bool, bool, bool, void*);
			Relocation<func_t*> func("", 0x755A50);
			return func(this, a_actor, a_form, a_extraList, a_count, a_slot, a_unk1, a_equipLock, a_unk2, a_unk3, a_unk4);
		}
	public:
	};
}