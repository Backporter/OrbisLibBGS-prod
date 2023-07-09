#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSSoundHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraCreatureMovementSound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCreatureMovementSound>;
	public:
		~ExtraCreatureMovementSound();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSoundHandle	handle;
		uint32_t		pad1C;
	};
	static_assert(sizeof(ExtraCreatureMovementSound) == 0x20);
}