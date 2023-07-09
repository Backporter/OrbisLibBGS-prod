#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class ExtraDistantData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kDistantData>;
	public:
		~ExtraDistantData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPoint3      landNormal;
		uint32_t 	  pad1C;
	};
	static_assert(sizeof(ExtraDistantData) == 0x20);
}