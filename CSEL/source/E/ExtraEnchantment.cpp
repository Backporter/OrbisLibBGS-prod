#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraEnchantment.h"

namespace ConsoleRE
{
	ExtraEnchantment::ExtraEnchantment() : ExtraEnchantment(nullptr, 0)
	{}

	ExtraEnchantment::ExtraEnchantment(EnchantmentItem* a_enchantment, uint16_t a_charge, bool a_removeOnUnequip) : BSExtraData(), enchantment(a_enchantment), charge(a_charge), removeOnUnequip(a_removeOnUnequip), pad1B(0), pad1C(0)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraEnchantment:.data.rel.ro", 0x1D1D5D8);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraEnchantment::GetType() const
	{
		return TypeID;
	}

	bool ExtraEnchantment::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraEnchantment*>(a_rhs);
		return enchantment != rhs->enchantment || charge != rhs->charge || removeOnUnequip != rhs->removeOnUnequip;
	}
}