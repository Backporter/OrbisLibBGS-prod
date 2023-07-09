#pragma once

#include "../B/BaseFormComponent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESQualityForm : public BaseFormComponent
	{
	public:
		~TESQualityForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		uint32_t quality;
	};
	static_assert(sizeof(TESQualityForm) == 0x10);
}