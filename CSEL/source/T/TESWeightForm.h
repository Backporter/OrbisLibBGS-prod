#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	// 0x10
	class TESWeightForm : public BaseFormComponent
	{
	public:
		~TESWeightForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		float weight;
	};
	static_assert(sizeof(TESWeightForm) == 0x10);
}