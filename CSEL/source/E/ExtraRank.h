#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraRank : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRank>;
	public:
		~ExtraRank();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		int32_t  rank;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraRank) == 0x18);
}