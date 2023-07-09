#pragma once

#include "../B/BGSLoadGameSubBuffer.h"
#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSavedAnimation : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSavedAnimation>;
	public:
		~ExtraSavedAnimation() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BGSLoadGameSubBuffer animationBuffer;
	};
	static_assert(sizeof(ExtraSavedAnimation) == 0x18);
}