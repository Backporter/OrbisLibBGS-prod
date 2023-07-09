#pragma once

#include "../B/BaseFormComponent.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BGSAttackDataMap;

	class BGSAttackDataForm : public BaseFormComponent
	{
	public:
		~BGSAttackDataForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		NiPointer<BGSAttackDataMap> attackDataMap;
	};
	static_assert(sizeof(BGSAttackDataForm) == 0x10);
}