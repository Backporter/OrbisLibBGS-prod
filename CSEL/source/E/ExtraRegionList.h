#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESRegionList;

	class ExtraRegionList : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRegionList>;
	public:
		~ExtraRegionList();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESRegionList* list;
	};
	static_assert(sizeof(ExtraRegionList) == 0x18);
}