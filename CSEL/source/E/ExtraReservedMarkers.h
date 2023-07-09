#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"
//

namespace ConsoleRE
{
	class ExtraReservedMarkers : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kReservedMarkers>;
	public:
		~ExtraReservedMarkers();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<void*> reservedMarkerArray;
		uint64_t		unk28;
	};
	static_assert(sizeof(ExtraReservedMarkers) == 0x28);
}