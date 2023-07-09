#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESBoundObject;
		
	class BGSMenuDisplayObject: public BaseFormComponent
	{
	public:
		~BGSMenuDisplayObject() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
		
		// add
		virtual TESBoundObject* GetMenuDisplayObject() const;
	public:
		TESBoundObject* menuDispObject;
	};
	static_assert(sizeof(BGSMenuDisplayObject) == 0x10);
}