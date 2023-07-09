#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraEnableStateChildren : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEnableStateChildren>;
	public:
		~ExtraEnableStateChildren();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<ObjectRefHandle> children;
	};
	static_assert(sizeof(ExtraEnableStateChildren) == 0x20);
}