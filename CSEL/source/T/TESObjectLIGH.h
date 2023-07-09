#pragma once

#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSEquipType.h"
#include "../C/Color.h"
#include "../F/FormTypes.h"
#include "../N/NiColor.h"
#include "../T/TESBoundAnimObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"


namespace ConsoleRE
{
	struct OBJ_LIGH
	{
	public:
		int32_t											 time;
		uint32_t										 radius;
		Color                                            color;
		uint32_t										 flags;
		float                                            fallofExponent;
		float                                            fov;
		float                                            nearDistance;
		float                                            flickerPeriodRecip;
		float                                            flickerIntensityAmplitude;
		float                                            flickerMovementAmplitude;
	};
	static_assert(sizeof(OBJ_LIGH) == 0x28);

	class TESObjectLIGH : 
		public TESBoundAnimObject, 
		public TESFullName, 
		public TESModelTextureSwap, 
		public TESWeightForm, 
		public TESValueForm, 
		public BGSDestructibleObjectForm, 
		public BGSEquipType
	{
	public:
		static constexpr int TypeID = 31;
	public:
		~TESObjectLIGH() override;

		// override (TESBoundAnimObject)
		void        InitializeData() override;
		bool        Load(TESFile* a_mod) override;
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;
		void        InitItemImpl() override;
		bool        Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		void        UnClone3D(TESObjectREFR* a_ref) override;
		NiAVObject* LoadGraphics(TESObjectREFR* a_ref) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;

		 // override (BGSEquipType)
		BGSEquipSlot* GetEquipSlot() override;
		void          SetEquipSlot(BGSEquipSlot* a_slot) override;
	public:
		OBJ_LIGH                data;
		float                   fade;
		uint32_t				pad10C;
		BGSSoundDescriptorForm* sound;
		NiColor                 emittanceColor;
		uint32_t				pad124;
		BGSLensFlare*           lensFlare;
	};
	static_assert(sizeof(TESObjectLIGH) == 0x100);

}