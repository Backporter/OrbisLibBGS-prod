#pragma once

#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSOpenCloseForm.h"
#include "../F/FormTypes.h"
#include "../T/TESBoundAnimObject.h"
#include "../T/TESFullName.h"
#include "../T/TESMagicTargetForm.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class TESObjectACTI :
		public TESBoundAnimObject,
		public TESFullName,
		public TESModelTextureSwap,
		public TESMagicTargetForm,
		public BGSDestructibleObjectForm,
		public BGSOpenCloseForm,
		public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 24;
	public:
		~TESObjectACTI() override;

		// override (TESBoundAnimObject)
		void          InitializeData() override;
		void          ClearData() override;
		bool          Load(TESFile* a_mod) override;
		void          SaveGame(BGSSaveFormBuffer* a_buf) override;
		void          LoadGame(BGSLoadFormBuffer* a_buf) override;
		void          InitItemImpl() override;
		bool          GetIgnoredBySandbox() const override;
		bool          IsWater() const override;
		bool          Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		TESWaterForm* GetWaterType() const override;
		bool          GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		bool          CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;
	public:
		BGSSoundDescriptorForm*                    soundLoop;
		BGSSoundDescriptorForm*                    soundActivate;
		TESWaterForm*                              waterForm;
		uint16_t								   flags;
		uint16_t								   padC2;
	};
	static_assert(sizeof(TESObjectACTI) == 0xC0);
}