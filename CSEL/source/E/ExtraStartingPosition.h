#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class BGSLocation;

	struct FILE_POS_ROT
	{
		NiPoint3 pos;
		NiPoint3 rot;
	};
	static_assert(sizeof(FILE_POS_ROT) == 0x18);

	class ExtraStartingPosition : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kStartingPosition>;
	public:
		~ExtraStartingPosition();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		FILE_POS_ROT startPosition;
		BGSLocation* location;
	};
	static_assert(sizeof(ExtraStartingPosition) == 0x30);
}