#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class AlchemyItem;

	class ExtraPoison : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPoison>;
	public:
		ExtraPoison();
		ExtraPoison(AlchemyItem* a_poison, int32_t a_count);
		~ExtraPoison() override = default;
		
		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		AlchemyItem*  poison;
		uint32_t	  count;
		uint32_t	  pad1C;
	};
	static_assert(sizeof(ExtraPoison) == 0x20);
}