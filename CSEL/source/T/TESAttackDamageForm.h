#pragma once

#include "../B/BaseFormComponent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESAttackDamageForm : public BaseFormComponent
	{
	public:
		~TESAttackDamageForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
		
		// add
		virtual uint16_t GetAttackDamage(void) const;
	public:
		uint16_t	attackDamage;
	};
	static_assert(sizeof(TESFullName) == 0x10);
}