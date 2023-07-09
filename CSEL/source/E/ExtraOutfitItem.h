#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraOutfitItem : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOutfitItem>;
	public:
		~ExtraOutfitItem();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t    id;
		uint32_t	pad14;
	};
	static_assert(sizeof(ExtraOutfitItem) == 0x18);
}