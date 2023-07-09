#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESTopicInfo;

	struct SayOnceTopicInfos
	{
		TESTopicInfo* info;
		int32_t		  dateStamp;
		float         hourStamp;
	};
	static_assert(sizeof(SayOnceTopicInfos) == 0x10);

	class ExtraSayTopicInfoOnceADay : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSayTopicInfoOnceADay>;
	public:
		~ExtraSayTopicInfoOnceADay();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<SayOnceTopicInfos*>* saidOnceTopicInfos;
	};
	static_assert(sizeof(ExtraSayTopicInfoOnceADay) == 0x18);
}