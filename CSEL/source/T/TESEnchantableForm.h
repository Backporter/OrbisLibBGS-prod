#pragma once

#include "../B/BaseFormComponent.h"
#include "../E/EnchantmentItem.h"

namespace ConsoleRE
{
	class TESEnchantableForm : public BaseFormComponent
	{
	public:
		~TESEnchantableForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		EnchantmentItem* formEnchanting;
		uint32_t		 castingType;
		uint32_t		 amountofEnchantment;
	};
	static_assert(sizeof(TESEnchantableForm) == 0x18);
}