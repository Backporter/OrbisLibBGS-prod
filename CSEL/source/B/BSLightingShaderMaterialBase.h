#pragma once

#include "../B/BSShaderMaterial.h"
#include "../N/NiColor.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSTextureSet;
	class NiSourceTexture;

	class BSLightingShaderMaterialBase : public BSShaderMaterial
	{
	public:
		~BSLightingShaderMaterialBase() override;

		// override (BSShaderMaterial)
		BSShaderMaterial* Create() override = 0;
		void              CopyMembers(BSShaderMaterial* a_other) override; 
		bool              DoIsCopy(BSShaderMaterial* a_other) override;
		uint32_t		  ComputeCRC32(void) override;
		BSShaderMaterial* GetDefault() override; 
		Feature           GetFeature() const override;
		Type              GetType() const override;

		// add
		virtual void OnLoadTextureSet(void);
		virtual void ClearTextures(void);
		virtual void ReceiveValuesFromRootMaterial(void);
		virtual void GetTextures(void);
		virtual void SaveBinary(void);
		virtual void LoadBinary(void);
	public:
		NiColor						specularColor;
		uint32_t					pad44;
		NiPointer<NiSourceTexture>	diffuseTexture;
		int32_t						diffuseRenderTargetSourceIndex;
		uint32_t					pad54;
		NiPointer<NiSourceTexture>	normalTexture;
		NiPointer<NiSourceTexture>	rimSoftLightingTexture;
		NiPointer<NiSourceTexture>	specularBackLightingTexture;
		int32_t						textureClampMode;
		int32_t						pad74;
		NiPointer<BSTextureSet>		textureSet;
		float						materialAlpha;
		float						refractionPower;
		float						specularPower;
		float						specularColorScale;
		float						subSurfaceLightRolloff;
		float						rimLightPower;
		uint32_t					unk90;
	};
	static_assert(sizeof(BSLightingShaderMaterialBase) == 0x98);
}