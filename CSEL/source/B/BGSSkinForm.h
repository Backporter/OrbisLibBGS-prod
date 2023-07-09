#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESObjectARMO;

	class BGSSkinForm : public BaseFormComponent
	{
	public:
		~BGSSkinForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		TESObjectARMO* skin;
	};
	static_assert(sizeof(BGSSkinForm) == 0x10);
}