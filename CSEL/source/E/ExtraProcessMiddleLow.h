#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraProcessMiddleLow : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kProcessMiddleLow>;
	public:
		~ExtraProcessMiddleLow();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t refCount;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraProcessMiddleLow) == 0x18);
}