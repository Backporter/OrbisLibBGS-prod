#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraBadPosition : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kBadPosition>;
	public:
		~ExtraBadPosition();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
	};
	static_assert(sizeof(ExtraBadPosition) == 0x10);
}