#pragma once

#include "../B/BGSBipedObjectForm.h"
#include "../B/BSTArray.h"
#include "../F/FormTypes.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESObject.h"
#include "../T/TESRaceForm.h"

namespace ConsoleRE
{
	struct OBJ_ARMA
	{
		int8_t		 priorities[2];
		int8_t		 modelRange[2];
		int8_t		 unused[2];
		int8_t		 detectionSoundValue;
		uint8_t		 pad07;
		float        weaponAdjust;
	};
	static_assert(sizeof(OBJ_ARMA) == 0xC);

	class TESObjectARMA : public TESObject, public TESRaceForm,  public BGSBipedObjectForm
	{
	public:
		static constexpr int TypeID = 102;
	public:
		~TESObjectARMA() override;  // 00

		// override (TESObject)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		OBJ_ARMA            data;
		uint32_t			pad04C;
		TESModelTextureSwap bipedModels[2][2];
		BGSTextureSet*      skinTextures[2];
		BGSListForm*        skinTextureSwapLists[2];
		BSTArray<TESRace*>  additionalRaces;
		BGSFootstepSet*	    footstepSet;
		BGSArtObject*	    artObject;
	};
	static_assert(sizeof(TESObjectARMA) == 0x170);
}