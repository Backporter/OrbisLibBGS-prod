#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSPreloadable : public BaseFormComponent
	{
	public:

		~BGSPreloadable() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
		
		virtual void Unk_02() = 0;
	public:
	};
	static_assert(sizeof(BGSPreloadable) == 0x8);
}