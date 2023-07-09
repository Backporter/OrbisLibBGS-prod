#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"
#include "../F/FactionRank.h"

namespace ConsoleRE
{
	class TESFaction;

	class ExtraFactionChanges : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFactionChanges>;
	public:
		~ExtraFactionChanges() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<FactionRank>	factionChanges;
		TESFaction*				crimeFaction;
		bool					removeCrimeFaction;
		uint8_t					pad31;
		uint16_t				pad32;
		uint32_t				pad34;
	};
	static_assert(sizeof(ExtraFactionChanges) == 0x30);
}