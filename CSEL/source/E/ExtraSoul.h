#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSoul : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSoul>;
	public:
		ExtraSoul();
		explicit ExtraSoul(uint8_t a_level);
		~ExtraSoul() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;

		//
		uint32_t GetContainedSoul() { return soul; }
	public:
		uint8_t soul;
	};
	static_assert(sizeof(ExtraSoul) == 0x18);
}