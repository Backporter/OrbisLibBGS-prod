#pragma once

#include "../B/BSTList.h"

namespace ConsoleRE
{
	class Actor;
	class ActiveEffect;
	class EffectItem;
	class EffectSetting;
	class MagicItem;
	class TESBoundObject;
	class TESObjectREFR;

	class MagicTarget
	{
	public:
		virtual ~MagicTarget();

		virtual bool                         AddTarget();
		virtual TESObjectREFR*               GetTargetStatsObject();
		virtual bool           				 MagicTargetIsActor();
		virtual bool                         IsInvulnerable();
		virtual void                         InvalidateCommandedActorEffect(ActiveEffect* a_effect);
		virtual bool                         CanAddActiveEffect() = 0;
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() = 0;
		virtual void                         EffectAdded(ActiveEffect*);
		virtual void                         EffectRemoved(ActiveEffect*);
		virtual void                         CheckResistance(MagicItem* a_magicItem, EffectItem* a_effect, TESBoundObject* a_object);
		virtual void                         CheckAbsorb(Actor* a_actor, MagicItem* a_magicItem, const EffectItem* a_effect);

		bool HasMagicEffect(EffectSetting* a_effect);
	public:
		void*	 postUpdateDispelList;
		uint8_t	 flags;
		uint8_t	 Unk0A;
		uint16_t Unk0C;
		uint32_t Unk10;
	};
	static_assert(sizeof(MagicTarget) == 0x18);
}