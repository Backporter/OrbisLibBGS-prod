#pragma once

#include "../B/BSLightingShaderMaterialBase.h"
#include "../N/NiColor.h"

namespace ConsoleRE
{
	class BSLightingShaderMaterialHairTint : public BSLightingShaderMaterialBase
	{
	public:
		~BSLightingShaderMaterialHairTint() override;

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                                // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		uint32_t		  ComputeCRC32(void) override;                      // 04
		Feature           GetFeature() const override;                      // 06 - { return Feature::kHairTint; }
		void              SaveBinary(void) override;                        // 0C
		void              LoadBinary(void) override;                        // 0D

	public:
		NiColor  tintColor;
	};
}