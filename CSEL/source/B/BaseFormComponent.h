#pragma once

#include "../../../OrbisUtil/include/Macro.h"

namespace ConsoleRE
{
	class BaseFormComponent
	{
	public:
		virtual ~BaseFormComponent();

		// add
		virtual void InitializeDataComponent() = 0;
		virtual void ClearDataComponent() = 0;
		virtual void CopyComponent(BaseFormComponent* a_rhs);
	public:
	};
	static_assert(sizeof(BaseFormComponent) == 0x8);
}
