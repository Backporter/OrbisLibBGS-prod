#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESImageSpaceModifier;

	class TESImageSpaceModifiableForm : public BaseFormComponent
	{
	public:
		~TESImageSpaceModifiableForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		TESImageSpaceModifier* imageSpaceModifier;
	};
}