#pragma once

#include "../B/BSLightingShaderMaterialBase.h"
#include "../N/NiColor.h"

namespace ConsoleRE
{
	class BSLightingShaderMaterialFacegenTint : public BSLightingShaderMaterialBase
	{
	public:
		~BSLightingShaderMaterialFacegenTint() override;

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;
		void              CopyMembers(BSShaderMaterial* a_other) override;
		uint32_t		  ComputeCRC32(void) override;
		Feature           GetFeature() const override;
		void              SaveBinary(void) override;
		void              LoadBinary(void) override;
	public:
		NiColor			  tintColor;
	};
	static_assert(sizeof(BSLightingShaderMaterialFacegenTint) == 0xA0);
}