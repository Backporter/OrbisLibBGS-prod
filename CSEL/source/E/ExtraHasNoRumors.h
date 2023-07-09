#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraHasNoRumors : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHasNoRumors>;
	public:
		~ExtraHasNoRumors();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		bool     noRumors;
		uint8_t  pad11;
		uint16_t pad12;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraHasNoRumors) == 0x18);
}