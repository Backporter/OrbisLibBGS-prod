#pragma once

#include "../B/BSExtraData.h"

namespace ConsoleRE
{
	class ExtraCount : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCount>;
	public:
		ExtraCount();
		explicit ExtraCount(int16_t a_count);
		~ExtraCount() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool	 IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint16_t  count;
	};
	static_assert(sizeof(ExtraCount) == 0x18);
}