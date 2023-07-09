#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class TESFile;
	class TESRegion;
	class TESRegionData;
	class TESRegionDataGrass;
	class TESRegionDataLandscape;
	class TESRegionDataMap;
	class TESRegionDataObjects;
	class TESRegionDataSound;
	class TESRegionDataWeather;

	class TESRegionDataManager
	{
	public:
		virtual ~TESRegionDataManager();

		// add
		virtual TESRegion*                   GetLastLoadedRegion();                               
		virtual TESRegionData*				 ConstructRegionData(uint32_t a_id) const;      
		virtual TESRegionDataObjects*        AsRegionDataObjects(TESRegionData* a_data) const;    
		virtual TESRegionDataWeather*        AsRegionDataWeather(TESRegionData* a_data) const;    
		virtual TESRegionDataMap*            AsRegionDataMap(TESRegionData* a_data) const;        
		virtual TESRegionDataLandscape*      AsRegionDataLandscape(TESRegionData* a_data) const;  
		virtual TESRegionDataGrass*          AsRegionDataGrass(TESRegionData* a_data) const;      
		virtual TESRegionDataSound*          AsRegionDataSound(TESRegionData* a_data) const;      
		virtual bool                         LoadRegionData(TESFile* a_file, TESRegion* a_region);
	public:
		TESRegion* lastLoadedRegion;
	};
	static_assert(sizeof(TESRegionDataManager) == 0x10);
}
