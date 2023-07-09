#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraItemDropper : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kItemDropper>;
	public:
		~ExtraItemDropper();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		ObjectRefHandle dropper;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraItemDropper) == 0x18);
}