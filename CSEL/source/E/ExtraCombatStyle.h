#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESCombatStyle;

	class ExtraCombatStyle : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCombatStyle>;
	public:
		~ExtraCombatStyle();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESCombatStyle* combatStyle;
	};
	static_assert(sizeof(ExtraCombatStyle) == 0x18);
}