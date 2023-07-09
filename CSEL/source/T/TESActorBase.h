#pragma once

#include "../A/ActorValueOwner.h"
#include "../B/BGSAttackDataForm.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSPerkRankArray.h"
#include "../B/BGSSkinForm.h"
#include "../F/FormTypes.h"
#include "../T/TESAIForm.h"
#include "../T/TESActorBaseData.h"
#include "../T/TESBoundAnimObject.h"
#include "../T/TESContainer.h"
#include "../T/TESFullName.h"
#include "../T/TESSpellList.h"

namespace ConsoleRE
{
	class TESActorBase :
		public TESBoundAnimObject, 
		public TESActorBaseData, 
		public TESContainer, 
		public TESSpellList, 
		public TESAIForm,
		public TESFullName, 
		public ActorValueOwner, 
		public BGSDestructibleObjectForm,  
		public BGSSkinForm, 
		public BGSKeywordForm, 
		public BGSAttackDataForm, 
		public BGSPerkRankArray
	{
	public:

		~TESActorBase() override;

		// add
		virtual bool				GetHasPLSpecTex() const;
		virtual TESCombatStyle*		GetCombatStyle();
		virtual void				SetCombatStyle(TESCombatStyle* a_combatStyle);
		
		// override (TESBoundAnimObject)
		bool						AddChange(uint32_t a_changeFlags) override;
		void						RemoveChange(uint32_t a_changeFlags) override;
		void						SaveGame(BGSSaveFormBuffer* a_buf) override;
		void						LoadGame(BGSLoadFormBuffer* a_buf) override;
		bool						IsAutoCalc() const override;
		void						SetAutoCalc(bool a_autoCalc) override;


		// override (ActorValueOwner)
		void						SetActorValue(uint32_t a_akValue, float a_value) override;
		float						GetActorValue(uint32_t a_akValue) override;
		float						GetPermanentActorValue(uint32_t a_akValue) override;
		float						GetBaseActorValue(uint32_t a_akValue) override;
		void						SetBaseActorValue(uint32_t a_akValue, float a_value) override;
		void						ModActorValue(uint32_t a_akValue, float a_value) override;
		void						RestoreActorValue(uint32_t a_modifier, uint32_t a_akValue, float a_value) override;
		bool						GetIsPlayerOwner() const override;
		
		//
		virtual TESForm*			GetAsForm();
	public:
	};
	static_assert(sizeof(TESActorBase) == 0x140);
}