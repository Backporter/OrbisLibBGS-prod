#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraUniqueID : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kUniqueID>;
	public:
		~ExtraUniqueID();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint32_t baseID;
		uint16_t uniqueID;
		uint16_t pad16;
	};
	static_assert(sizeof(ExtraUniqueID) == 0x18);
}