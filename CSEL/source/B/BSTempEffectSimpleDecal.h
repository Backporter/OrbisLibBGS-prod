#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTempEffect.h"
#include "../N/NiColor.h"
#include "../N/NiFrustumPlanes.h"
#include "../N/NiMatrix3.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BGSDecalNode;
	class BGSTextureSet;
	class BSTriShape;
	class NiAVObject;

	class BSTempEffectSimpleDecal : public BSTempEffect
	{
	public:
		~BSTempEffectSimpleDecal() override;

		// override (BSTempEffect)
		const NiRTTI*             GetRTTI() const override;
		void                      Initialize() override;
		void                      Attach() override;
		bool                      Update(float a_arg1) override;
		NiAVObject*				  Get3D() const override;
	public:
	};
}