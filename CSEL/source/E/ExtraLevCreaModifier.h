#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraLevCreaModifier : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLevCreaModifier>;
	public:
		~ExtraLevCreaModifier();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint32_t modifier;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraLevCreaModifier) == 0x18);
}