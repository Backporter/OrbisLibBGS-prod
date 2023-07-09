#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraDroppedItemList : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kDroppedItemList>;
	public:
		~ExtraDroppedItemList();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<ObjectRefHandle> droppedItemList;
	};
	static_assert(sizeof(ExtraDroppedItemList) == 0x20);
}