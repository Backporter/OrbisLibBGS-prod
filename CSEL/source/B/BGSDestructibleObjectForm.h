#pragma once

#include "../B/BaseFormComponent.h"
#include "../F/FormTypes.h"
#include "../N/NiSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	class QueuedFile;
	class TESModelTextureSwap;

	struct DestructibleObjectStage
	{
	public:
		enum class DESTRUCTIBLE_OBJECT_STAGE_FLAGS
		{
			kNone = 0,
			kCapDamage = 1 << 0,
			kDisableObject = 1 << 1,
			kDestroyObject = 1 << 2,
			kIgnoreExternalDamage = 1 << 3,
			kBecomesDynamic = 1 << 4
		};
	public:
		int8_t														modelDamageStage;
		int8_t														healthPercentage;
		uint8_t														flags;
		uint8_t														pad03;
		uint32_t													selfDamagePerSecond;
		BGSExplosion*                                               explosion;
		BGSDebris*                                                  debris;
		uint32_t													debrisCount;
		uint32_t													pad1C;
		TESModelTextureSwap*                                        replacementModel;
	};
	static_assert(sizeof(DestructibleObjectStage) == 0x28);

	struct DestructibleObjectData
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kVatsTargetable = 1 << 0
		};
	public:
		uint32_t                        health;
		int8_t                          numStages;
		uint8_t							flags;
		uint16_t                        pad06;
		DestructibleObjectStage**       stages;
		volatile int32_t				replacementModelRefCount;
		uint32_t						pad14;
		NiPointer<QueuedFile>           preloadedReplacementModels;
	};
	static_assert(sizeof(DestructibleObjectData) == 0x20);

	class BGSDestructibleObjectForm : public BaseFormComponent
	{
	public:
		~BGSDestructibleObjectForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		DestructibleObjectData* data;
	};
	static_assert(sizeof(BGSDestructibleObjectForm) == 0x10, "#");
}