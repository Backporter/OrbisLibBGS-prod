#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraMagicCaster : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMagicCaster>;
	public:
		~ExtraMagicCaster();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
	};
}