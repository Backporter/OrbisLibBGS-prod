#pragma once

#include "../B/BSTSmartPointer.h"
#include "../B/BSTempEffect.h"
#include "../N/NiMatrix3.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSGeometry;
	class NiAVObject;
	class BGSTextureSet;
	class QueuedTempEffect;

	class BSTempEffectGeometryDecal : public BSTempEffect
	{
	public:
		~BSTempEffectGeometryDecal() override;

		// override (BSTempEffect)
		const NiRTTI*                  GetRTTI() const override;
		void                           Initialize() override;
		void                           Attach() override;
		bool                           Update(float a_arg1) override;
		NiAVObject*                    Get3D() const override;
		uint32_t					   GetType() const override;
	public:
		NiPointer<BSGeometry>             decal;
		NiPointer<BSGeometry>             attachedGeometry;
		NiPointer<NiNode>                 attachedGeometryParent;
		NiPointer<NiNode>                 decalNode;
		BSTSmartPointer<QueuedTempEffect> queuedDecal;
		BGSTextureSet*                    texSet;
		BGSTextureSet*                    texSet2;
		NiMatrix3                         rotation;
		NiPoint3                          origin;
		NiPoint3                          direction;
		float                             width;
		uint32_t						  unkA8;
		uint32_t						  flags;
		bool                              unkB0;
	};
	static_assert(sizeof(BSTempEffectGeometryDecal) == 0xB0);
}