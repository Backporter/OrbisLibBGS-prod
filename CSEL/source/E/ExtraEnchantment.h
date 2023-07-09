#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../F/FormTypes.h"

namespace ConsoleRE
{
	// 0x20
	class ExtraEnchantment : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEnchantment>;
	public:
		ExtraEnchantment();
		ExtraEnchantment(EnchantmentItem* a_enchantment, uint16_t a_charge, bool a_removeOnUnequip = false);
		~ExtraEnchantment() override = default;

		// override(BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		EnchantmentItem* enchantment;
		uint16_t		 charge;
		bool			 removeOnUnequip;
		uint8_t			 pad1B;
		uint32_t		 pad1C;
	};
	static_assert(sizeof(ExtraEnchantment) == 0x20);
}