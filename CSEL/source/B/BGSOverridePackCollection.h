#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSListForm;

	class BGSOverridePackCollection : public BaseFormComponent
	{
	public:
		~BGSOverridePackCollection() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		BGSListForm* spectatorOverRidePackList;
		BGSListForm* observeCorpseOverRidePackList;
		BGSListForm* guardWarnOverRidePackList;
		BGSListForm* enterCombatOverRidePackList;
	};
	static_assert(sizeof(BGSOverridePackCollection) == 0x28);
}