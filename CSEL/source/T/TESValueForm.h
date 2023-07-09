#pragma once

#include "../B/BaseFormComponent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESValueForm : public BaseFormComponent
	{
	public:
		~TESValueForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		int32_t value;
	};
	static_assert(sizeof(TESValueForm) == 0x10);
}