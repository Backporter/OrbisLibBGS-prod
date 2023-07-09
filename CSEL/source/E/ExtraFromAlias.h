#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraFromAlias : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFromAlias>;
	public:
		~ExtraFromAlias();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESQuest*   quest;
		uint32_t 	aliasID;
		uint32_t 	pad1C;
	};
	static_assert(sizeof(ExtraFromAlias) == 0x20);
}