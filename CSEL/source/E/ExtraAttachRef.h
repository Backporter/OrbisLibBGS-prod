#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAttachRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAttachRef>;
	public:
		~ExtraAttachRef() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t ashPileRef;
		uint32_t pad14;
	};
}