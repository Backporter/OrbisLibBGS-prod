#include "../Weather/PapyrusExtWeather.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESWeather.h"

namespace PapyrusExtWeather
{
	// I really hate doing this...
	using namespace ConsoleRE;

	float GetSunGlare(TESWeather* thisWeather)
	{
		return (thisWeather) ? (thisWeather->sunGlare / 256.0) : 0.0;
	}
	
	float GetSunDamage(TESWeather* thisWeather)
	{
		return (thisWeather) ? (thisWeather->sunDamage / 256.0) : 0.0;
	}
	
	float GetWindDirection(TESWeather* thisWeather)
	{
		return (thisWeather) ? (thisWeather->windDirection / (256.0 / 360.0)) : 0.0;
	}
	
	float GetWindDirectionRange(TESWeather* thisWeather)
	{
		return (thisWeather) ? (thisWeather->windDirectionRange / (256.0 / 180.0)) : 0.0;
	}
	
	float GetFogDistance(TESWeather* thisWeather, bool day, uint32_t fdType)
	{
		if (!thisWeather)
			return 0.0;
	
		switch (fdType)
		{
		case 0:
			return day ? thisWeather->dayNear : thisWeather->nightNear;
			break;
		case 1:
			return day ? thisWeather->dayFar : thisWeather->nightFar;
			break;
		case 2:
			return day ? thisWeather->dayPower : thisWeather->nightPower;
			break;
		case 3:
			return day ? thisWeather->dayMax : thisWeather->nightMax;
			break;
		}
	
		return 0.0;
	}

	bool RegisterWeather(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSunGlare),           TESWeather, float>                ("GetSunGlare",            "Weather", GetSunGlare));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSunDamage),          TESWeather, float>                ("GetSunDamage",           "Weather", GetSunDamage));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWindDirection),      TESWeather, float>                ("GetWindDirection",       "Weather", GetWindDirection));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWindDirectionRange), TESWeather, float>                ("GetWindDirectionRange",  "Weather", GetWindDirectionRange));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFogDistance),        TESWeather, float, bool, uint32_t>("GetFogDistance",         "Weather", GetFogDistance));

		return true;
	}
}