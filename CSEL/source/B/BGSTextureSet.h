#pragma once

#include "../B/BSTextureSet.h"
#include "../D/DecalData.h"
#include "../I/ID.h"
#include "../T/TESBoundObject.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class BGSTextureSet : public TESBoundObject, public BSTextureSet
	{
	public:
		static constexpr int TypeID = 7;

		~BGSTextureSet() override;

		// override (TESBoundObject)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref, bool a_arg3) override;
		void        UnClone3D(TESObjectREFR* a_ref) override;
	public:
		TESTexture		Textures[Textures::kTotal];
		DecalData*		decalData;
		uint16_t		flags;
		uint16_t		UnkC2;
		BSResource::ID	textureFileIDs[Textures::kTotal];
	};
	static_assert(sizeof(BGSTextureSet) == 0x128);
}