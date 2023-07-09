#pragma once

#include "../B/BGSLoadGameSubBuffer.h"
#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSavedHavokData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSavedHavokData>;
	public:
		~ExtraSavedHavokData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BGSLoadGameSubBuffer havokBuffer;
	};
	static_assert(sizeof(ExtraSavedHavokData) == 0x18);
}