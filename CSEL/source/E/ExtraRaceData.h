#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class ExtraRaceData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRaceData>;
	public:
		~ExtraRaceData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<QueuedFile> preloadedRaceData;
	};
	static_assert(sizeof(ExtraRaceData) == 0x18);
}