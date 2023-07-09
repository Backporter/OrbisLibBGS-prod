#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAttachRefChildren : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAttachRefChildren>;
	public:
		~ExtraAttachRefChildren() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<ObjectRefHandle> children;
	};
	static_assert(sizeof(ExtraAttachRefChildren) == 0x20);
}