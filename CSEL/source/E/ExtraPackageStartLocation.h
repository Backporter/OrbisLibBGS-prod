#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class TESForm;

	struct WORLD_LOCATION
	{
		TESForm* locationForm;
		NiPoint3 locPt;
		float    zRot;
	};
	static_assert(sizeof(WORLD_LOCATION) == 0x18);

	class ExtraPackageStartLocation : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPackageStartLocation>;
	public:
		~ExtraPackageStartLocation();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		WORLD_LOCATION worldLoc;
	};
	static_assert(sizeof(ExtraPackageStartLocation) == 0x28);
}