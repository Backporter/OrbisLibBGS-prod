#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESGlobal;

	class ExtraGlobal : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kGlobal>;
	public:
		~ExtraGlobal();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESGlobal* global;
	};
	static_assert(sizeof(ExtraGlobal) == 0x18);
}