#pragma once
#include "../B/BGSActionData.h"
#include "../B/BSSoundHandle.h"

#include "../D/DialogueItem.h"

#include "../T/TESShout.h"

#include "../N/NiRefObject.h"

#include "../S/StandardDetectionListener.h"

#include <stdint.h>
#include <stddef.h>

namespace ConsoleRE
{
	enum class VOICE_STATE
	{
		kNone = 0,
		kRequest = 1,
		kStart = 2,
		kContinue = 3,
		kPrecast = 4,
		kPostcast = 5,
		kFail = 6
	};

	struct DetectionEvent
	{
	public:
		uint32_t		actionValue;  // 00
		NiPoint3        location;     // 00
		float			timeStamp;    // 10
		uint32_t		ref;          // 10
	};
	static_assert(sizeof(DetectionEvent) == 0x18, "");

	// 0x468
	class AIProcess_High
	{
	public:
		struct HEAD_TRACK_TYPES
		{
			enum HEAD_TRACK_TYPE : uint32_t
			{
				kDefault = 0,
				kAction,
				kScript,
				kCombat,
				kDialogue,
				kProcedure,

				kTotal = 6
			};
		};
		using HEAD_TRACK_TYPE = HEAD_TRACK_TYPES::HEAD_TRACK_TYPE;

		class Data180 : public BSIntrusiveRefCounted
		{
		public:
			struct Data
			{
			public:
				struct UnkData
				{
					uint64_t unk00;
					uint64_t unk08;
					uint64_t unk10;
					uint64_t unk18;
					uint64_t unk20;
					uint64_t unk28;
					uint64_t unk30;
					uint64_t unk38;
					uint64_t unk40;
					uint64_t unk48;
					uint64_t unk50;
					uint64_t unk58;
					uint64_t unk60;
					uint64_t unk68;
					uint64_t unk70;
					uint64_t unk78;
				};
				static_assert(sizeof(UnkData) == 0x80, "");
			public:
				UnkData*      unk00;
				uint64_t	  unk08;
			};
			static_assert(sizeof(Data) == 0x10, "");
		public:
			uint32_t			unk04;
			BSTSmallArray<Data> unk08;
			uint64_t			unk28;
		};

		struct UnkData2
		{
		public:
			uint64_t	  unk00;
			uint64_t	  unk08;
			uint64_t	  unk10;
			uint64_t	  unk18;
			uint64_t	  unk20;
			uint64_t	  unk28;
			UnkData2*      next;
		};
		static_assert(sizeof(UnkData2) == 0x38, "");
	public:
		void ClearHeadtrackTarget(uint32_t a_headtrackType, bool a_defaultHold)
		{
			using func_t = void(AIProcess_High* const, uint32_t, bool);
			Relocation<func_t*> func("", 0x781490);
			return func(this, a_headtrackType, a_defaultHold);
		}
	public:
		uint32_t											  voiceState;
		uint32_t											  Unk04;
		TESShout*                                             currentShout;
		uint32_t											  currentShoutVariation;
		float                                                 voiceTimeElapsed;
		float                                                 voiceRecoveryTime;
		float                                                 healthRegenDelay;
		float                                                 staminaRegenDelay;
		float                                                 magickaRegenDelay;
		float                                                 unk028;
		uint32_t											  unk02C;
		BSTArray<uint32_t>									  lastSpokenToArray;
		uint64_t											  unk040;
		uint32_t											  numSequences;
		uint64_t											  Unk50;
		BSTHashMap<BSFixedString, BGSActionData*>			  actions;
		NiPoint3                                              pathingCurrentMovementSpeed;
		NiPoint3                                              pathingCurrentRotationSpeed;
		NiPoint3                                              pathingDesiredPosition;
		NiPoint3                                              pathingDesiredOrientation;
		NiPoint3                                              pathingDesiredMovementSpeed;
		NiPoint3                                              pathingDesiredRotationSpeed;
		uint64_t											  unk0C0;
		uint32_t											  lastExtDoorActivated;
		float                                                 activationHeight;
		uint32_t											  unk0D0;
		uint32_t											  unk0D4;
		uint64_t											  unk0D8;
		BSFixedString                                         voiceSubtitle;				  // 0E0
		float                                                 unk0E8;                         // 0E8
		float                                                 unk0EC;                         // 0EC
		float                                                 unk0F0;                         // 0F0
		float                                                 unk0F4;                         // 1F4
		float                                                 unk0F8;                         // 1F8
		float                                                 unk0FC;                         // 1FC
		float                                                 unk100;                         // 100
		float                                                 unk104;                         // 104
		float                                                 unk108;                         // 108
		float                                                 unk10C;                         // 10C
		float                                                 unk110;                         // 110
		float                                                 unk114;                         // 114
		float                                                 unk118;                         // 118
		float                                                 unk11C;                         // 11C
		uint32_t											  fadeState;                      // 120
		uint32_t											  unk124;                         // 124
		uint64_t											  unk128;                         // 128
		uint64_t											  unk130;                         // 130
		uint64_t											  unk138;                         // 138
		uint64_t											  unk140;                         // 140
		uint64_t											  unk148;                         // 148
		float                                                 headTrackTargetTimer;           // 150
		NiPoint3                                              headTrackTargetOffset;          // 154
		float                                                 headTrackHoldOffsetHoldTimer;   // 160
		float                                                 headTrackTargetOffsetTimer;     // 164
		uint32_t											  lastTarget;                     // 168
		uint32_t											  pathLookAtTarget;               // 16C
		void*                                                 unk170;                         // 170 - smart ptr
		void*                                                 unk178;                         // 178 - smart ptr
		BSTSmartPointer<Data180>                              unk180;                         // 180
		BSTSmartPointer<Data180>                              unk188;                         // 188
		float                                                 unk190;                         // 190
		float                                                 unk194;                         // 194
		float                                                 unk198;                         // 198
		uint32_t											  unk19C;                         // 19C
		uint64_t											  unk1A0;                         // 1A0
		uint64_t											  unk1A8;                         // 1A8
		uint64_t											  unk1B0;                         // 1B0
		uint64_t											  unk1B8;                         // 1B8
		uint64_t											  unk1C0;                         // 1C0
		uint64_t											  unk1C8;                         // 1C8
		uint64_t											  unk1D0;						  // 1D0
		float                                                 unk1D8;                         // 1D0
		float                                                 cachedActorHeight;              // 1DC
		NiPointer<NiRefObject>                                unk1E0;                         // 1E8
		uint32_t											  unk1E8;                         // 1F0
		float                                                 unk1EC;                         // 1F4
		uint32_t											  unk1F0;                         // 1F8
		float                                                 unk1F4;                         // 1FC
		float                                                 unk1F8;                         // 200
		uint32_t											  unk1FC;                         // 204
		UnkData2*                                             unk200;                         // 208
		uint64_t											  unk208;                         // 210
		BSFixedString                                         unk210;                         // 210
		BSTArray<void*>										  knowledgeArray;                 // 218
		mutable BSReadWriteLock                               knowledgeLock;                  // 228
		BSTArray<void*>										  queueofGreetings;               // 238
		void*												  attackData;                     // 248
		NiPoint3                                              locationOffsetByWaterPoint;     // 250
		uint32_t											  unk25C;                         // 25C
		uint64_t											  unk260;                         // 260
		float                                                 unk268;                         // 268
		NiPoint3                                              deathForceDirection;            // 26C
		float                                                 deathForce;                     // 278
		float                                                 unk27C;                         // 27C
		float                                                 unk280;                         // 280
		float                                                 unk284;                         // 284
		float                                                 unk288;                         // 288
		float                                                 clearTalkToListTimer;           // 28C
		float                                                 maxAlpha;                       // 290
		float                                                 unk294;                         // 294
		uint64_t											  unk298;                         // 298
		float                                                 unk2A0;                         // 2A0 - fAISocialTimerForConversationsMin
		uint32_t											  unk2A4;                         // 2A4
		uint64_t											  unk2A8;                         // 2A8
		uint64_t											  unk2B0;                         // 2B0
		uint64_t											  unk2B8;                         // 2B8
		uint64_t											  unk2C0;                         // 2C0
		uint32_t											  unk2C8;                         // 2C8
		NiPoint3                                              leftWeaponLastPos;              // 2CC
		NiPoint3                                              rightWeaponLastPos;             // 2D8
		uint32_t											  greetActor;                     // 2E4
		float                                                 soundDelay;                     // 2E8
		BSSoundHandle                                         soundHandles[2];                // 2EC
		float                                                 greetingTimer;                  // 304
		float                                                 exclusiveTimer;                 // 308
		float                                                 idleTimer;                      // 30C
		float                                                 detectGreetTimer;               // 310
		float                                                 breathTimer;                    // 314, after this this is sketch OK?.
		uint64_t											  unk318;                         // 318
		uint64_t											  unk320;                         // 320
		uint64_t											  unk328;                         // 328
		float                                                 closeDialogueTimer;             // 330
		uint32_t											  unk334;                         // 334
		uint64_t											  unk338;                         // 338
		uint32_t                                              unk340;                         // 340
		uint32_t											  unk344;                         // 344
		uint64_t											  unk348;                         // 348
		BSTSmartPointer<DialogueItem>                         greetTopic;                     // 350
		uint32_t											  unk358;                         // 358
		uint32_t                                              unk35C;                         // 35C
		void*                                                 unk360;                         // 360
		uint64_t											  unk368;                         // 368
		void*												  healthBarNode;                  // 370, NiPointer<NiBillboardNode>
		float                                                 unk378;                         // 378
		uint32_t											  unk37C;                         // 37C
		uint32_t											  numberGuardsPursuing;           // 380
		float                                                 reEquipArmorTimer;              // 384
		BSSimpleList<SpellItem*>*                             leveledSpellList;               // 388
		float                                                 detectionModifier;              // 390
		float                                                 detectionModifierTimer;         // 394
		float                                                 lightLevel;                     // 398
		float                                                 sceneHeadTrackTimer;            // 39C
		float                                                 pCapVoiceFailsafeTimer;         // 3A0
		uint32_t											  unk3A4;                         // 3A4
		void*                                                 unk3A8;                         // 3A8
		uint64_t											  unk3B0;                         // 3B0
		void*												  unk3B8;                         // 3B8
		uint32_t											  unk3C0;                         // 3C0
		uint32_t											  unk3C4;                         // 3C4
		DetectionEvent*										  actorsGeneratedDetectionEvent;  // 3C8
		NiPointer<StandardDetectionListener>				  detectionListener;              // 3D0
		uint64_t											  unk3D8;                         // 3D8
		void*                                                 unk3E0;                         // 3E0 - smart ptr
		uint64_t											  unk3E8;                         // 3E8
		uint8_t												  unk3F0[0x18];                   // 3F0, ????
		NiPoint3                                              animationDelta;                 // 408
		NiPoint3                                              animationAngleMod;              // 40C
		void*												  unk420;                         // 420
		uint64_t											  unk428;                         // 428
		void*												  crimeToReactTo;                 // 430
		uint64_t											  unk438;                         // 438
		uint64_t											  unk440;                         // 440
		uint8_t												  unk448;                         // 448
		bool                                                  inCommandState;                 // 449
		uint8_t												  unk44A;                         // 44A
		uint8_t												  unk44B;                         // 44B
		uint32_t											  unk44C;                         // 44C
		uint16_t											  unk450;                         // 450
		bool                                                  arrested;                       // 452
		bool                                                  unk453;                         // 453
		bool                                                  unk454;                         // 454
		bool                                                  unk455;                         // 455
		bool                                                  unk456;                         // 456
		bool                                                  unk457;                         // 457
		bool                                                  farGeometry;                    // 458
		bool                                                  unk459;                         // 459
		bool                                                  unk45A;                         // 45A
		bool                                                  unk45B;                         // 45B
		bool                                                  unk45C;                         // 45C
		bool                                                  unk45D;                         // 45D
		bool                                                  unk45E;                         // 45E
		bool                                                  unk45F;                         // 45F
		bool                                                  unk460;                         // 460
		bool                                                  unk461;                         // 461
		bool                                                  unk462;                         // 462
		uint8_t												  unk463;                         // 463
		uint32_t											  unk464;                         // 464
	};
	static_assert(offsetof(AIProcess_High, leftWeaponLastPos)			== 0x2CC, "");
	static_assert(offsetof(AIProcess_High, rightWeaponLastPos)			== 0x2D8, "");
	static_assert(offsetof(AIProcess_High, cachedActorHeight)			== 0x1DC, "");
	static_assert(offsetof(AIProcess_High, lastTarget)					== 0x168, "");
	static_assert(offsetof(AIProcess_High, pathLookAtTarget)			== 0x16C, "");
	static_assert(offsetof(AIProcess_High, lastExtDoorActivated)		== 0xC8,  "");
	static_assert(offsetof(AIProcess_High, unk0D0)						== 0xD0,  "");
	static_assert(offsetof(AIProcess_High, pathingCurrentMovementSpeed) == 0x78,  "");
	static_assert(offsetof(AIProcess_High, lastSpokenToArray)			== 0x30,  "");
	static_assert(offsetof(AIProcess_High, headTrackTargetOffset)		== 0x154, "");
	static_assert(offsetof(AIProcess_High, actions)						== 0x58,  "");
	static_assert(offsetof(AIProcess_High, breathTimer)					== 0x314, "");
	static_assert(offsetof(AIProcess_High, arrested)				    == 0x452, "");
	static_assert(sizeof(AIProcess_High)								== 0x468, "");
}