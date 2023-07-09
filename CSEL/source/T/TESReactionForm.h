#pragma once

#include "../B/BSTList.h"
#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESForm;

	struct GROUP_REACTION
	{
		TESForm*	form;
		int32_t		reaction;
		int32_t		fightReaction;
	};
	static_assert(sizeof(GROUP_REACTION) == 0x10);

	class TESReactionForm : public BaseFormComponent
	{
	public:
		~TESReactionForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		BSSimpleList<GROUP_REACTION*>    reactions;
		uint8_t							 groupFormType;
	};
	static_assert(sizeof(TESReactionForm) == 0x20);
}