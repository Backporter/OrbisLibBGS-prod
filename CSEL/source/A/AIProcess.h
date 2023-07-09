#pragma once

#include "../A/AIProcess_MiddleHigh.h"
#include "../A/AIProcess_High.h"

#include "../B/bhkCharacterController.h"

#include "../T/TESForm.h"
#include "../T/TESTopic.h"

#include <stdint.h>

namespace ConsoleRE
{
	struct Data0B8
	{
	public:
		void*			unk00;
		Data0B8*		unk08;
		void*			unk10;
		void*			unk18;
		uint64_t		unk20;
		void*			unk28;
		uint32_t		unk30;
		uint32_t		pad34;
	};
	static_assert(sizeof(Data0B8) == 0x38, "");

	// 0x140, ctor = sub_760DE0/sub_787F20
	class AIProcess
	{
	public:
		TESForm* GetEquippedInLeftHand()  { return equippedObjects[0]; /* Relocation<TESForm*(*)(decltype(this))> func(__FUNCDNAME__, 0x766FA0); return func(this);*/ }
		TESForm* GetEquippedInRightHand() { return equippedObjects[1]; /* Relocation<TESForm*(*)(decltype(this))> func("", 0x766FB0); return func(this); */ }

		bool	 InHighProcess()
		{
			if (!processLevel)
				return true;

			return false;
		}

		bool	 InMiddleHighProcess()
		{
			if (!processLevel || processLevel == 1)
				return true;

			return false;
		}

		bhkCharacterController* GetCharController()
		{
			if (middleHigh)
				return middleHigh->charController.T1;
			else
				return nullptr;

			/* Relocation<bhkCharacterController*(*)(decltype(this))> _GetCharacterController(__FUNCTION__, 0x7B17A0); return _GetCharacterController(this);*/
		}

		// Actor* GetUserData()
		// {
		// 	auto torsoNode = middleHigh ? middleHigh->torsoNode : nullptr;
		// 	auto userData = torsoNode ? torsoNode->GetUserData() : nullptr;
		// 
		// 	return userData ? static_cast<Actor*>(userData) : nullptr;
		// }
		
		// due to inlining, high->SetHeadtrackTarget is here.
		void SetHeadtrackTarget(uint32_t a_headtrackType, TESObjectREFR* a_target)
		{
			using func_t = void(AIProcess* const, uint32_t, TESObjectREFR*);
			Relocation<func_t*> func("", 0x7813A0);
			return func(this, a_headtrackType, a_target);
		}
	public:
		int32_t*										middleLow;
		AIProcess_MiddleHigh*							middleHigh;
		AIProcess_High*									high;
		ActorPackage									currentPackage;
		float											Unk50;
		uint32_t										Unk54;
		void*											cachedValues;
		int32_t											numberItemsActivate;
		uint32_t										Unk64;
		BSSimpleList<void*>								objects;
		BSSimpleList<TESObjectREFR*>                    genericLocations;
		void*											acquireObject;
		void*											savedAcquireObject;
		float                                           essentialDownTimer;
		float                                           deathTime;
		float                                           trackedDamage;
		uint32_t										UnkA4;
		BSTArray<TESForm*>                              forms;
		Data0B8											UnkB8;
		TESForm*                                        equippedObjects[2];
		uint64_t										Unk100;
		uint64_t										Unk108;
		uint32_t										Unk110;
		uint32_t										target;
		uint64_t										Unk118;
		uint64_t										Unk120;
		TESTopic*										Unk128;
		uint32_t										Unk130;
		uint16_t										Unk134;
		uint8_t											Unk136;
		uint8_t											lowProcessFlags;
		uint8_t											processLevel;
		bool                                            skippedTimeStampForPathing;
		bool                                            ignoringCombat;
		bool                                            endAlarmOnActor;
		bool                                            escortingPlayer;
	public:
	};
	static_assert(offsetof(AIProcess, lowProcessFlags) == 0x137, "");
	static_assert(offsetof(AIProcess, Unk50) == 0x50, "");
	static_assert(offsetof(AIProcess, forms) == 0xA8, "");
	static_assert(offsetof(AIProcess, equippedObjects) == 0xF0, "");
	static_assert(sizeof(AIProcess) == 0x140, "sizeof(AIProcess) != 0x140");
}