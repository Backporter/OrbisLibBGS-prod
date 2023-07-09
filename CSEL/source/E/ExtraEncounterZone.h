#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSEncounterZone;

	class ExtraEncounterZone : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEncounterZone>;
	public:
		ExtraEncounterZone();
		explicit ExtraEncounterZone(BGSEncounterZone* a_zone);
		~ExtraEncounterZone() override = default;

		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSEncounterZone* zone;
	};
	static_assert(sizeof(ExtraEncounterZone) == 0x18);
}