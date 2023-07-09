#include "../B/BSEffectShaderData.h"

#include "../N/NiTexture.h"

namespace ConsoleRE
{
	BSEffectShaderData::BSEffectShaderData() :
		BSIntrusiveRefCounted(),
		pad04(0),
		nodeFilterFunction(nullptr),
		baseTexture(nullptr),
		paletteTexture(nullptr),
		blockOutTexture(nullptr),
		textureClampMode(3),
		fillColor(),
		rimColor(),
		baseFillScale(1.0),
		baseFillAlpha(1.0),
		baseRimAlpha(1.0),
		uOffset(0.0),
		vOffset(0.0),
		uScale(1.0),
		vScale(1.0),
		edgeExponent(1.0),
		boundDiameter(0.0),
		srcBlend(std::underlying_type_t<NiAlphaProperty::AlphaFunction>(NiAlphaProperty::AlphaFunction::kSrcAlpha)),
		destBlend(std::underlying_type_t<NiAlphaProperty::AlphaFunction>(NiAlphaProperty::AlphaFunction::kInvSrcAlpha)),
		zTestFunc(1),
		alphaTestRef(0),
		grayscaleToColor(false),
		grayscaleToAlpha(false),
		ignoreTextureAlpha(false),
		baseTextureProjectedUVs(false),
		ignoreBaseGeomTexAlpha(false),
		lighting(false),
		alpha(false),
		pad84(0)
	{}

	BSEffectShaderData::~BSEffectShaderData()
	{}
}