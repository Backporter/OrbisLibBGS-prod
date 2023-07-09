#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESDescription : public BaseFormComponent
	{
	public:
		~TESDescription() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		uint32_t fileOffset;
		uint32_t descriptionText;
	};
	static_assert(sizeof(TESDescription) == 0x10, "#");
}