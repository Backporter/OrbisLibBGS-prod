#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraUsedMarkers : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kUsedMarkers>;
	public:
		~ExtraUsedMarkers();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<void*> usedMarkers;
	};
	static_assert(sizeof(ExtraUsedMarkers) == 0x20);
}