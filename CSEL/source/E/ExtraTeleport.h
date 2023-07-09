#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	struct DoorTeleportData
	{
		ObjectRefHandle linkedDoor;
		NiPoint3        position;
		NiPoint3        rotation;
		int8_t			flags;
		uint8_t			pad1D;
		uint16_t		pad1E;
	};
	static_assert(sizeof(DoorTeleportData) == 0x20);

	class ExtraTeleport : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kTeleport>;
	public:
		~ExtraTeleport();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		DoorTeleportData* teleportData;
	};
	static_assert(sizeof(ExtraTeleport) == 0x18);
}