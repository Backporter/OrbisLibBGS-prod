#pragma once

#include "../B/BGSDirectionalAmbientLightingColors.h"
#include "../I/InteriorData.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSLightingTemplate : public TESForm
	{
	public:
		static constexpr int TypeID = 108;

		~BGSLightingTemplate() override;
	public:
		INTERIOR_DATA                       data;
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors;
	};
}