#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraTerminalState : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kTerminalState>;
	public:
		~ExtraTerminalState();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint64_t unk10;
	};
	static_assert(sizeof(ExtraTerminalState) == 0x18);
}