#pragma once

#include "../B/BaseFormComponent.h"
#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class TESFullName : public BaseFormComponent
	{
	public:
		~TESFullName() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add
		virtual uint32_t	GetFullNameLength(void);
		virtual const char* GetFullName(void);
	public:
		BSFixedString name;
	};
	static_assert(sizeof(TESFullName) == 0x10);
}