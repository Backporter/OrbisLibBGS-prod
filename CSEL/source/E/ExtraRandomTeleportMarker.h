#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	class ExtraRandomTeleportMarker : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRandomTeleportMarker>;
	public:
		~ExtraRandomTeleportMarker();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESObjectREFR* marker;
	};
	static_assert(sizeof(ExtraRandomTeleportMarker) == 0x18);
}