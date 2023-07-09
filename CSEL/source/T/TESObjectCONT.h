#pragma once

#include "../T/TESBoundAnimObject.h"
#include "../T/TESContainer.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../T/TESFullName.h"
#include "../T/TESMagicCasterForm.h"
#include "../T/TESMagicTargetForm.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESWeightForm.h"

namespace ConsoleRE
{
	struct CONT_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kAllowsSoundsWhenAnimation = 1 << 0,
			kRespawn = 1 << 1,
			kShowOwner = 1 << 2
		};
	public:
		uint8_t flags;  // 0
	};
	static_assert(sizeof(CONT_DATA) == 0x1);

	class TESObjectCONT : 
		public TESBoundAnimObject, 
		public TESContainer, 
		public TESFullName, 
		public TESModelTextureSwap, 
		public TESWeightForm,
		public TESMagicCasterForm,
		public TESMagicTargetForm,
		public BGSDestructibleObjectForm,
		public BGSOpenCloseForm
	{
	public:
		static constexpr int TypeID = 28;
	public:
		~TESObjectCONT() override;

		// override (TESBoundAnimObject)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		bool GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		bool CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;

		// override (BGSOpenCloseForm)
		void HandleOpen(TESObjectREFR* a_target, TESObjectREFR* a_activator) override;
		void HandleClose(TESObjectREFR* a_target, TESObjectREFR* a_activator) override;
	public:
		CONT_DATA               data;
		uint16_t				padBA;
		BGSSoundDescriptorForm* openSound;
		BGSSoundDescriptorForm* closeSound;
	};
	static_assert(sizeof(TESObjectCONT) == 0xC8);
}