#pragma once

#include "../B/BaseFormComponent.h"
#include "../F/FormTypes.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BGSEquipType : public BaseFormComponent
	{
	public:
		~BGSEquipType() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add
		virtual BGSEquipSlot* GetEquipSlot();
		virtual void		  SetEquipSlot(BGSEquipSlot*);
	public:
		BGSEquipSlot* equipSlot;
	};
	static_assert(sizeof(BGSEquipType) == 0x10);
}