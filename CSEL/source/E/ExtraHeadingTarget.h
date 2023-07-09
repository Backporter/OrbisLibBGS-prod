#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraHeadingTarget : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHeadingTarget>;
	public:
		~ExtraHeadingTarget();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		ObjectRefHandle target;
		uint32_t   		pad14;
	};
	static_assert(sizeof(ExtraHeadingTarget) == 0x18);
}