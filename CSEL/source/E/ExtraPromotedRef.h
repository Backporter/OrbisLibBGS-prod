#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"
#include "../F/FormTypes.h"

namespace ConsoleRE
{
	class ExtraPromotedRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPromotedRef>;
	public:
		~ExtraPromotedRef();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<TESForm*> promotedRefOwners;
	};
	static_assert(sizeof(ExtraPromotedRef) == 0x20);
}