#pragma once

#include "../A/ActorPackage.h"
#include "../B/BSTEvent.h"
#include "../B/BSTList.h"
#include "../B/BGSPerkEntry.h"
#include "../N/NiPoint3.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSResponse.h"
#include "../B/BSFixedString.h"
#include "../D/DoNothingUnhandledPolicy.h"
#include "../N/NiSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	class Actor;
	class NiAVObject;
	class NiNode;
	class BSFaceGenNiNode;
	class BSLightingShaderProperty;
	class ActiveEffect;
	class BSAnimationGraphManager;
	class TESIdleForm;
	struct BSAnimationGraphVariableCache;
	class bhkCharacterController;
	class bhkRagdollPenetrationUtil;
	class InventoryEntryData;
	class TESObjectREFR;
	class QueuedFile;

	struct AIPerkData
	{
	public:
		BSTArray<BGSPerkEntry*>& at(uint8_t a_pos)
		{
			return operator[](a_pos);
		}

		BSTArray<BGSPerkEntry*>& operator[](uint8_t a_pos)
		{
			assert(a_pos < 92);
			return perkEntryArrays[a_pos];
		}
	public:
		BSTArray<BGSPerkEntry*> perkEntryArrays[92];
	};

	// 0x318
	class AIProcess_MiddleHigh
	{
	public:
		BSTEventSource<void*>																						Unk000;
		ActorPackage																								runOncePackage;
		BSTArray<int32_t>																							deadDetectList;
		BSSimpleList<TESObjectREFR*>																				refListChairBed;
		NiPoint3																									rotation;
		NiPoint3																									rotationSpeed;
		NiPoint3																									actorMountPosition;
		NiPoint3																									furniturePathPoint;
		NiPoint3																									lastSeenPosition;
		uint32_t																									bleedoutAttacker;
		int32_t																										wardState;
		uint32_t																									UnkE4;
		BSTSmartPointer<BSResponse<BSFixedString, Actor, BSFixedString, DoNothingUnhandledPolicy>>					animResponse;
		BSTArray<void*>																								commandedActors;
		NiNode*																										damageRootNode[6];
		uint64_t																									Unk130;
		NiNode*																										weaponBone;
		NiAVObject*																									headNode;
		NiAVObject*																									torsoNode;
		NiAVObject*																									faceTargetSourceNode;
		BSFaceGenNiNode*																							faceNodeSkinned;
		NiPointer<BSLightingShaderProperty>																			lightingProperty;
		uint64_t																									Unk168;
		void*																										itemstoEquipUnequip;
		void*																										lastHitData;
		void*																										headDeferredHideLimb;
		BSSimpleList<ActiveEffect*>*																				activeEffects;
		BSTSmartPointer<BSAnimationGraphManager>																	animationGraphManager;
		BSAnimationGraphVariableCache*																				animationVariableCache;
		BSTArray<void*>																								unk1A0;
		BSTArray<void*>																								unk1B0;
		mutable BSSpinLock																							unk1C0;
		void*																										unk1D0;
		uint16_t																									unk1D8;
		uint16_t																									unk1DA;
		uint32_t																									unk1DC;
		uint32_t																									unk1E0;
		float																										headHeightOffset;
		uint32_t																									occupiedFurniture;
		uint32_t																									unk1EC;
		uint64_t																									unk1F0;
		uint32_t																									commandingActor;
		uint32_t																									Unk1FC;
		InventoryEntryData*																							leftHand;
		TESIdleForm*																								furnitureIdle;
		void*																										unk210;
		uint64_t																									unk218;
		uint64_t																									unk220;
		uint64_t																									unk228;
		NiPointer<bhkCharacterController> 																			charController;              // 230, NiPointer<bhkCharacterController>
		BSTSmartPointer<bhkRagdollPenetrationUtil> 																	penetrationDetectUtil;       // 238, BSTSmartPointer<bhkRagdollPenetrationUtil> 
		InventoryEntryData*																							rightHand;
		InventoryEntryData*																							bothHands;
		NiPointer<QueuedFile>																						bodyPartPreload;			// after this this is sketch OK?.
		void*																										unk258;
		uint64_t																									unk260;
		AIPerkData*																									perkData;
		uint32_t																									unk270;
		uint32_t																									currentFurnitureSubgraphID;
		float																										unk1;
		float																										unk2;
		float																										unk3;
		float																										unk4;
		float																										unk5;
		float																										unk6;
		float																										unk7;
		float																										unk8;
		float																										unk9;
		float																										unk10;
		float																										unk11;
		float																										unk12;
		float																										alphaMult;
		float																										scriptRefractPower;
		float																										unk13;
		float																										deferredKillTimer;
		float																										killMoveTimer;
		float																										unk14;
		uint32_t																									unk15;
		uint32_t																									unk16;
		uint32_t																									currentFurnitureMarkerID;
		uint32_t																									unk17;
		uint64_t																									unk18;
		uint32_t																									unk19;
		uint32_t																									unk20;
		uint32_t																									unk21;
		uint16_t																									unk22;
		uint16_t																									unk23;
		uint64_t																									unk24;
		uint8_t																										unk25;
		uint8_t																										update3DModel;
		uint16_t																									unk26;
		uint16_t																									unk27;
		bool																										unk28;
		bool																										unk29;
		bool																										unk30;
		bool																										unk31;
		bool																										unk32;
		bool																										pickPocketed;
		bool																										summonedCreature; // 300?
		bool																										unk33;
		bool																										unk34;
		bool																										unk35;
		bool																										unk36;
		bool																										unk37;
		bool																										beenAttacked;
		bool																										unk38;
		bool																										unk39;
		bool																										unk40;
		bool																										unk41;
		bool																										unk42;
		bool																										unk43;
		bool																										unk44;
		bool																										unk45;
		bool																										unk46;
		bool																										unk47;
		bool																										unk48;
		bool																										unk49;
		bool																										unk50;
		bool																										unk51;
		bool																										unk52;
		bool																										unk53;
		bool																										Unk54;
		uint32_t																									Unk55;
	};
	static_assert(sizeof(AIProcess_MiddleHigh) == 0x318, "");
}