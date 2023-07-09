#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	enum class BREADCRUMB_STATE
	{
		kInvalid = 0,
		kOnGround = 1,
		kInWater = 2
	};

	struct ExtraFollowerSwimBreadcrumb
	{
		NiPoint3 startLocation;
		uint32_t startNavMeshID;
		NiPoint3 endLocation;
		uint32_t endNavMeshID;
		bool     enteringWater;
		uint8_t  pad21;
		uint16_t pad22;
	};
	static_assert(sizeof(ExtraFollowerSwimBreadcrumb) == 0x24);

	class ExtraFollowerSwimBreadcrumbs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFollowerSwimBreadcrumbs>;
	public:
		~ExtraFollowerSwimBreadcrumbs();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t									leaderState;
		NiPoint3									leaderLocation;
		uint32_t									leaderNavMeshID;
		uint32_t									pad24;
		BSSimpleList<ExtraFollowerSwimBreadcrumb*>	crumbs;
	}; 
	static_assert(sizeof(ExtraFollowerSwimBreadcrumbs) == 0x38);

}