#pragma once

#include "../B/BSTArray.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSLensFlareSpriteRenderData;

	class BSLensFlareRenderData
	{
	public:
		float                                            fadeDistRadiusScale;
		float                                            colorInfluence;
		BSTArray<NiPointer<BSLensFlareSpriteRenderData>> sprites;
	};
}