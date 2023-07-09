#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraGhost : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kGhost>;
	public:
		~ExtraGhost();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		bool        ghost;
		uint8_t  	pad11;
		uint16_t 	pad12;
	};
	static_assert(sizeof(ExtraGhost) == 0x18);
}