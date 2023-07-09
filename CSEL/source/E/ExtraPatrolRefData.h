#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct PatrolRefData
	{
		uint64_t unk00;
		uint64_t unk08;
		uint64_t unk10;
		uint64_t unk18;
		uint64_t unk20;
	};
	static_assert(sizeof(PatrolRefData) == 0x28);

	class ExtraPatrolRefData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPatrolRefData>;
	public:
		~ExtraPatrolRefData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		PatrolRefData* patrolData;
	};
	static_assert(sizeof(ExtraPatrolRefData) == 0x18);
}