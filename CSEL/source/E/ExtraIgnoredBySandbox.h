#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraIgnoredBySandbox : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kIgnoredBySandbox>;
	public:
		~ExtraIgnoredBySandbox();

		// override (BSExtraData)
		uint32_t GetType() const override;
	};
	static_assert(sizeof(ExtraIgnoredBySandbox) == 0x10);
}