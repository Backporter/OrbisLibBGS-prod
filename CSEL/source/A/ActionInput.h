#pragma once

#include "../A/ActorState.h"
#include "../B/BGSAction.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BGSAnimationSequencer;

	class ActionInput
	{
	public:
		virtual ~ActionInput();

		// add
		virtual ActorState*            GetSourceActorState() const;
		virtual void                   Unk_02(void);
		virtual BGSAnimationSequencer* GetSourceSequencer() const;
	public:
		NiPointer<TESObjectREFR> source;
		NiPointer<TESObjectREFR> target;
		BGSAction*               action;
		uint32_t                 unk20;
	};
	static_assert(sizeof(ActionInput) == 0x28);
}