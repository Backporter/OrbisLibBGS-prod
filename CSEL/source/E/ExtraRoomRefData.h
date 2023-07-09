#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSLightingTemplate;
	class TESImageSpace;

	struct RoomRefData
	{
		BSSimpleList<ObjectRefHandle> portalList;
		BSSimpleList<ObjectRefHandle> roomList;
		int8_t						  master;
		uint8_t						  pad21;
		uint16_t					  pad22;
		uint32_t					  pad24;
		BGSLightingTemplate*          lightingTemplate;
		TESImageSpace*                imageSpace;
	};
	static_assert(sizeof(RoomRefData) == 0x38);

	class ExtraRoomRefData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRoomRefData>;
	public:
		~ExtraRoomRefData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		RoomRefData* data;
	};
	static_assert(sizeof(ExtraRoomRefData) == 0x18);
}