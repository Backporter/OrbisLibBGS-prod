#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../N/NiPoint2.h"

namespace ConsoleRE
{
	class BSShaderMaterial : public BSIntrusiveRefCounted
	{
	public:
		enum class Feature
		{
			kNone = -1,
			kDefault = 0,
			kEnvironmentMap = 1,
			kGlowMap = 2,
			kParallax = 3,
			kFaceGen = 4,
			kFaceGenRGBTint = 5,
			kHairTint = 6,
			kParallaxOcc = 7,
			kMultiTexLand = 8,
			kLODLand = 9,
			kMultilayerParallax = 11,
			kTreeAnim = 12,
			kMultiIndexTriShapeSnow = 14,
			kLODObjectsHD = 15,
			kEye = 16,
			kCloud = 17,
			kLODLandNoise = 18,
			kMultiTexLandLODBlend = 19
		};

		enum class Type
		{
			kBase = 0,
			kEffect = 1,
			kLighting = 2,
			kWater = 3
		};
	public:
		virtual ~BSShaderMaterial();

		// add
		virtual BSShaderMaterial* Create();                                
		virtual void              CopyMembers(BSShaderMaterial* a_other);
		virtual bool              DoIsCopy(BSShaderMaterial* a_other);
		virtual uint32_t		  ComputeCRC32(void);
		virtual BSShaderMaterial* GetDefault();
		virtual Feature           GetFeature() const;
		virtual Type              GetType() const;
	public:
		NiPoint2 texCoordOffset[2];
		NiPoint2 texCoordScale[2];
		uint32_t hashKey;
	};
	static_assert(sizeof(BSShaderMaterial) == 0x30);
}