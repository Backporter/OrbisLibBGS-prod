#pragma once

#include "../B/BSTList.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct TEXTURE_HAVOK_DATA
	{
		int32_t friction;
		int32_t restitution;
	};
	static_assert(sizeof(TEXTURE_HAVOK_DATA) == 0x8);

	class TESLandTexture : public TESForm 
	{
	public:
		static constexpr int TypeID = 20;
	public:
		~TESLandTexture() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BGSTextureSet*          textureSet;
		TEXTURE_HAVOK_DATA      havokData;
		BGSMaterialType*        materialType;
		int8_t					specularExponent;
		uint8_t					pad39;
		uint16_t				pad3A;
		int32_t					shaderTextureIndex;
		BSSimpleList<TESGrass*> textureGrassList;
	};
	static_assert(sizeof(TESLandTexture) == 0x50);
}