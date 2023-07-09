#pragma once

#include "../A/AITimeStamp.h"
#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraFriendHits : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFriendHits>;
	public:
		~ExtraFriendHits();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<AITimeStamp> hits;
	};
	static_assert(sizeof(ExtraFriendHits) == 0x20);
}