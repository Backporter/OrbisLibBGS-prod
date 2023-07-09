#pragma once

namespace ConsoleRE
{
	class BSTimer
	{
	public:
		uint64_t Unk00;
		uint64_t lastPerformanceCount; // = sceKernelGetProcessTimeCounter();
		float    clamp;
		float    clampRemainder;
		float    delta;
		float    realTimeDelta;
		uint32_t unk20;
		uint32_t unk24;
		float    unk28;
		uint32_t unk2C;
		uint32_t unk30;
		uint32_t unk34;
		uint8_t  unk38;
		uint8_t  unk39;
		bool     useGlobalTimeMultiplierTarget;
		uint8_t  pad3B;
		uint32_t pad3C;
	};
	static_assert(sizeof(BSTimer) == 0x40);
}