#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraTimeLeft : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kTimeLeft>;
	public:
		~ExtraTimeLeft();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		float    time;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraTimeLeft) == 0x18);
}