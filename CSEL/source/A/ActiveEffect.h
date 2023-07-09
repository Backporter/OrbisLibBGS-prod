#pragma once

#include "../A/ActiveEffectReferenceEffectController.h"
#include "../B/BSFixedString.h"
#include "../B/BSSoundHandle.h"
#include "../B/BSTList.h"
#include "../M/MagicSystem.h"
#include "../N/NiSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	class Actor;
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class EffectSetting;
	class MagicItem;
	class MagicTarget;
	class NiNode;
	class NiPoint3;
	class ReferenceEffect;
	class TESBoundObject;
	struct Effect;

	class ActiveEffect
	{
	public:
		static constexpr int TypeID = 142;
	public:
		virtual void			AdjustForPerks(Actor* a_caster, MagicTarget* a_target);
		virtual void			OnAdd(MagicTarget* a_target);
		virtual void			Unk_04(void);
		virtual TESObjectREFR*	GetVisualsTarget();
		virtual void			Update(float a_delta);
		virtual void			EvaluateConditions(float a_delta, bool a_forceUpdate);
		virtual bool			IsCausingHealthDamage();
		virtual void			SetLocation(const NiPoint3& a_location);
		virtual void			LoadGame(BGSSaveFormBuffer* a_buf);
		virtual void			SaveGame(BGSLoadFormBuffer* a_buf);
		virtual void			FinishLoadGame(BGSLoadFormBuffer* a_buf);
		virtual void			Revert(BGSLoadFormBuffer* a_buf);
		virtual int32_t			Compare(ActiveEffect* a_otherEffect);
		virtual void			HandleEvent(const BSFixedString& a_eventName);
		virtual void			SwitchAttachedRoot(uint64_t a_arg2, NiNode* a_attachRoot);
		virtual void			Unk_17(void);
		virtual bool			ShouldDispelOnDeath() const;
		virtual bool			GetAllowMultipleCastingSourceStacking();
		virtual void			ClearTargetImpl();

		virtual	~ActiveEffect();

		virtual void			Start();
		virtual void			Finish();
		virtual void			Unk_25(void);
		virtual bool			CheckCustomSkillUseConditions() const;
		virtual float			GetCustomSkillUseMagnitudeMultiplier(float a_mult) const;
	public:
		ActiveEffectReferenceEffectController hitEffectController;
		BSSoundHandle						  persistentSound;
		uint32_t							  caster;
		NiPointer<NiNode>					  sourceNode;
		MagicItem*                            spell;
		Effect*								  effect;
		MagicTarget*                          target;
		TESBoundObject*                       source;
		BSSimpleList<ReferenceEffect*>*       hitEffects;
		MagicItem*                            displacementSpell;
		float                                 elapsedSeconds;
		float                                 duration;
		float                                 magnitude;
		uint32_t							  flags;
		uint32_t							  conditionStatus;	
		uint16_t                              usUniqueID;
		uint16_t                              pad86;
		MagicSystem::CastingSource            castingSource;
		uint32_t                              pad8C;
	};
	static_assert(sizeof(ActiveEffect) == 0x90);
}