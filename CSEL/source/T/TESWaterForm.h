#pragma once

#include "../C/Color.h"
#include "../F/FormTypes.h"
#include "../N/NiColor.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESAttackDamageForm.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class BSWaterShaderMaterial;
	class NiTexture;

	struct WaterShaderData
	{
		struct DepthProperties
		{
			float reflections;
			float refraction;
			float normals;
			float specularLighting;
		};
		static_assert(sizeof(DepthProperties) == 0x10);

		float           unk00;
		float           unk04;
		float           unk08;
		float           unk0C;
		float           sunSpecularPower;
		float           reflectionAmount;
		float           fresnelAmount;
		uint32_t		unk1C;
		float           aboveWaterFogDistNear;
		float           aboveWaterFogDistFar;
		Color           shallowWaterColor;
		Color           deepWaterColor;
		Color           reflectionWaterColor;
		uint32_t		unk34;
		float           unk38;
		float           unk3C;
		float           unk40;
		float           unk44;
		float           displacementSize;
		float           displacementForce;
		float           displacementVelocity;
		float           displacementFalloff;
		float           displacementDampener;
		float           unk5C;
		float           noiseFalloff;
		float           noiseWindDirectionA[3];
		float           noiseWindSpeedA[3];
		float           unk7C;
		float           unk80;
		float           aboveWaterFogAmount;
		float           unk88;
		float           underwaterFogAmount;
		float           underwaterFogDistNear;
		float           underwaterFogDistFar;
		float           refractionMagnitude;
		float           specularPower;
		float           unkA0;
		float           specularRadius;
		float           specularBrightness;
		float           uvScaleA[3];
		float           amplitudeA[3];
		float           reflectionMagnitude;
		float           sunSparkleMagnitude;
		float           sunSpecularMagnitude;
		DepthProperties depthProperties;
		float           sunSparklePower;
		float           flowmapScale;
	};
	static_assert(sizeof(WaterShaderData) == 0xE8);

	class TESWaterForm : public TESForm, public TESFullName, public TESAttackDamageForm
	{
	public:
		static constexpr int TypeID = 84;

		~TESWaterForm() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool GetDangerous() const override;
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
	public:
		bool								 needUpdate;
		uint8_t								 pad41;
		uint16_t							 pad42;
		NiColorA							 texScroll[3];
		TESTexture							 noiseTextures[4];
		int8_t								 alpha;
		uint8_t								 flags;
		uint16_t							 pad0BA;
		BGSMaterialType*					 materialType;
		BGSSoundDescriptorForm*				 waterSound;
		WaterShaderData						 data;
		TESWaterForm*                        waterWeatherControl[3];
		int32_t								 currentTextureSelect[2];
		uint32_t							 frequencyX;
		uint32_t							 frequencyY;
		int32_t								 octaves;
		float                                amplitude;
		float                                lacunarity;
		float                                bias;
		float                                gain;
		uint32_t							 pad1F4;
		SpellItem*                           contactSpell;
		NiPointer<NiTexture>                 noiseTextureData[4];
		TESObjectACTI*                       placeableAutoWater;
		TESObjectACTI*                       placeableLODWater;
		BSWaterShaderMaterial*               waterShaderMaterial;
		bool                                 resetNoiseTextures;
		uint8_t								 pad239;
		uint16_t							 pad23A;
		TESImageSpace*                       imageSpace;
		NiPoint3                             linearVelocity;
		NiPoint3                             angularVelocity;
	};
	static_assert(sizeof(TESWaterForm) == 0x258);
}