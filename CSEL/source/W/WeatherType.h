#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class TESGlobal;
	class TESWeather;

	struct WeatherType
	{
	public:
		TESWeather*		weather;
		uint32_t		chance;
		uint32_t		unk0C;
		TESGlobal*		global;
	};
	static_assert(sizeof(WeatherType) == 0x18);
}
