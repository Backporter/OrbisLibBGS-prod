#pragma once

#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSOpenCloseForm.h"
#include "../B/BSTArray.h"
#include "../F//FormTypes.h"
#include "../T/TESBoundAnimObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class TESObjectDOOR : public TESBoundAnimObject, public TESFullName, public TESModelTextureSwap, public BGSDestructibleObjectForm, public BGSOpenCloseForm
	{
	public:
		static constexpr int TypeID = 29;
	public:
		~TESObjectDOOR() override;

		// override (TESBoundAnimObject)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		bool        Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;
		bool        GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		bool        CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;
		
		// override (BGSOpenCloseForm)
		void HandleOpen(TESObjectREFR* a_target, TESObjectREFR* a_activator) override;
	public:
		BGSSoundDescriptorForm*				openSound;
		BGSSoundDescriptorForm*				closeSound;
		BGSSoundDescriptorForm*				loopSound;
		uint8_t								flags;
		uint8_t								padB1;
		uint16_t							padB2;
		BSTArray<TESForm*>					randomTeleports;
	};
	static_assert(sizeof(TESObjectDOOR) == 0xB8);
}