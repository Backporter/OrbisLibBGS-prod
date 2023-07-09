#pragma once

#include "../B/BSSimpleList.h"
#include "../T/TESRegionData.h"

namespace ConsoleRE
{
	struct WeatherType;

	class TESRegionDataWeather : public TESRegionData
	{
	public:
		~TESRegionDataWeather() override;

		// override (TESRegionData)
		Type               GetType() const override;
		void               ConstructSelf() override;
		void               Unk_05(void) override;
		void               CopyFrom(TESRegionData* a_src, bool a_copy) override;
		bool			   IsLoaded() const override;                            

		// add
		virtual void Unk_08(void);
	public:
		BSSimpleList<WeatherType*> weatherTypes;
	};
	static_assert(sizeof(TESRegionDataWeather) == 0x20);
}
