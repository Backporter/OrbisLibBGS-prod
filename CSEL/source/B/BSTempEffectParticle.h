#pragma once

#include "../B/BSSoundHandle.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSTempEffect.h"
#include "../N/NiMatrix3.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiTransform.h"

namespace ConsoleRE
{
	class BGSParticleObjectCloneTask;
	class NiAVObject;
	class NiNode;

	class BSTempEffectParticle : public BSTempEffect
	{
	public:
		~BSTempEffectParticle() override;

		const NiRTTI*                  GetRTTI() const override;
		void                           Detach() override;
		bool                           Update(float a_arg1) override;
		uint32_t					   GetType() const override;
	public:
		NiPointer<NiAVObject>                       particle3D;
		BSTSmartPointer<BGSParticleObjectCloneTask> cloneTask;
		const char*                                 modelName;
		NiPointer<NiNode>                           dynamicCellNode;
		NiTransform                                 particleTransform;
		uint32_t									flags;
		NiPointer<NiAVObject>                       unk88;
		NiTransform                                 unk88Transform;
		uint32_t									padC4;
		uint64_t									unkC8;
		BSSoundHandle                               sound1;
		BSSoundHandle                               sound2;
		uint8_t										unkE8;
		uint8_t										padE9;
		uint16_t									unkEA;
		uint32_t									unkEC;
	};
	static_assert(sizeof(BSTempEffectParticle) == 0xE8);
}