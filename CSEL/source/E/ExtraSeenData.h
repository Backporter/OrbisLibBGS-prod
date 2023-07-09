#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class SeenData;

	class ExtraSeenData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSeenData>;
	public:
		~ExtraSeenData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		SeenData* seenData;
	};
}