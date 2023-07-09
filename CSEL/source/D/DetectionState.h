#pragma once

#include "../N/NiPoint3.h"
#include "../N/NiRefObject.h"

namespace ConsoleRE
{
	class DetectionState : public NiRefObject
	{
	public:
		~DetectionState() override;
	public:
		int32_t		level;
		uint8_t		unk14;
		uint8_t		unk15;
		uint8_t		unk16;
		uint8_t		pad17;
		float       unk18;
		NiPoint3    unk1C;
		float       unk28;
		NiPoint3    unk2C;
		float       unk38;
		NiPoint3    unk3C;
	};
	static_assert(sizeof(DetectionState) == 0x48);
}