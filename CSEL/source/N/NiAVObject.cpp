#include "../N/NiAVObject.h"

//#include "../B/BSEffectShaderData.h"
#include "../B/BSGeometry.h"
#include "../B/BSLightingShaderMaterialFacegenTint.h"
#include "../B/BSLightingShaderMaterialHairTint.h"
#include "../B/BSLightingShaderProperty.h"
#include "../B/BSShaderMaterial.h"
#include "../B/BSShaderProperty.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSVisit.h"
#include "../N/NiColor.h"
#include "../N/NiNode.h"
#include "../N/NiProperty.h"
#include "../N/NiRTTI.h"

//#include "../S/State.h"

#include "../Offsets_NiRTTI.h"

namespace ConsoleRE
{
	void NiAVObject::Update(NiUpdateData& a_data)
	{
		using func_t = decltype(&NiAVObject::Update);
		Relocation<func_t> func("", 0xE7B4D0);
		return func(this, a_data);
	}

	uint32_t NiAVObject::UpdateBodyTint(const NiColor& a_color)
	{
		return (uint32_t) BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl
		{
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) 
			{
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect, *ConsoleRE::NiRTTI_BSLightingShaderProperty.get());
				if (lightingShader) 
				{
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kFaceGenRGBTint) 
					{
						auto facegenTint = static_cast<BSLightingShaderMaterialFacegenTint*>(material);
						facegenTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	uint32_t NiAVObject::UpdateHairColor(const NiColor& a_color)
	{
		return (uint32_t)BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl
		{
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect)
			{
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect, *ConsoleRE::NiRTTI_BSLightingShaderProperty.get());
				if (lightingShader)
				{
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kHairTint)
					{
						auto hairTint = static_cast<BSLightingShaderMaterialHairTint*>(material);
						hairTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}
}