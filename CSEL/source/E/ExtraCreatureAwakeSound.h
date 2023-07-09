#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSSoundHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraCreatureAwakeSound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCreatureAwakeSound>;
	public:
		~ExtraCreatureAwakeSound();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSoundHandle	handle;
		uint32_t		pad1C;
	};
	static_assert(sizeof(ExtraCreatureAwakeSound) == 0x20);
}