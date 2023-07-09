#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraHealth : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHealth>;
	public:
		ExtraHealth();
		explicit ExtraHealth(float a_health);
		~ExtraHealth() override = default;
		
		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		float         health;
		uint32_t	  pad14;
	};
	static_assert(sizeof(ExtraHealth) == 0x18);
}