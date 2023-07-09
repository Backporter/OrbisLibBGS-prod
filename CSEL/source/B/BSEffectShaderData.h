#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../N/NiAlphaProperty.h"
#include "../N/NiColor.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiTexture;

	// 0x187DB0
	class BSEffectShaderData : public BSIntrusiveRefCounted
	{
	public:
		using NodeFilterFunction_t = bool(const BSFixedString*);

		BSEffectShaderData();
		~BSEffectShaderData();
	public:
		uint32_t						  pad04;
		NodeFilterFunction_t*             nodeFilterFunction;
		NiPointer<NiTexture>              baseTexture;
		NiPointer<NiTexture>              paletteTexture;
		NiPointer<NiTexture>              blockOutTexture;
		uint32_t						  textureClampMode;
		NiColorA                          fillColor;
		NiColorA                          rimColor;
		float                             baseFillScale;
		float                             baseFillAlpha;
		float                             baseRimAlpha;
		float                             uOffset;
		float                             vOffset;
		float                             uScale;
		float                             vScale;
		float                             edgeExponent;
		float                             boundDiameter;
		uint32_t						  srcBlend;
		uint32_t						  destBlend;
		uint32_t						  zTestFunc;
		int8_t							  alphaTestRef;
		bool                              grayscaleToColor;
		bool                              grayscaleToAlpha;
		bool                              ignoreTextureAlpha;
		bool                              baseTextureProjectedUVs;
		bool                              ignoreBaseGeomTexAlpha;
		bool                              lighting;
		bool                              alpha;
		uint32_t						  pad84;
	};
	static_assert(sizeof(BSEffectShaderData) == 0x88);
}