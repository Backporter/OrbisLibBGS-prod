#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraLargeRefOwnerCells : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLargeRefOwnerCells>;
	public:
		~ExtraLargeRefOwnerCells();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<TESForm*> ownerCells;
		uint64_t		   unk28;
	};
	static_assert(sizeof(ExtraLargeRefOwnerCells) == 0x28);
}