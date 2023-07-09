#pragma once

#include "../B/BSVolumetricLightingRenderData.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSVolumetricLighting : public TESForm, public BSVolumetricLightingRenderData
	{
	public:
		static constexpr int TypeID = 137;

		~BGSVolumetricLighting() override;
	public:
	};
}