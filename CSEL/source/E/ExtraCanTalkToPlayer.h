#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraCanTalkToPlayer : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCanTalkToPlayer>;
	public:
		~ExtraCanTalkToPlayer() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		bool     talk;
		uint8_t  pad11;
		uint16_t pad12;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraCanTalkToPlayer) == 0x18);
}