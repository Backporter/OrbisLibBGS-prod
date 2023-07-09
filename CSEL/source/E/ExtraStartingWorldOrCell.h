#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESForm;
	class ExtraStartingWorldOrCell : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kStartingWorldOrCell>;
	public:
		~ExtraStartingWorldOrCell();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESForm* startingWorldOrCell;
	};
	static_assert(sizeof(ExtraStartingWorldOrCell) == 0x18);
}