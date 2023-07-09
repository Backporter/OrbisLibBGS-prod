#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraFavorCost : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFavorCost>;
	public:
		~ExtraFavorCost();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		float    cost;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraFavorCost) == 0x18);
}