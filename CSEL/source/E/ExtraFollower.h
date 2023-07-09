#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraFollower : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFollower>;

		struct FollowerInfo
		{
			ActorHandle actor;
			float       intendedFollowDistance;
		};
		static_assert(sizeof(FollowerInfo) == 0x8);
	public:
		~ExtraFollower();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<FollowerInfo> actorFollowers;
	};
	static_assert(sizeof(ExtraFollower) == 0x20);
}