#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESRegionData.h"

namespace ConsoleRE
{
	class TESRegionDataMap : public TESRegionData
	{
	public:
		~TESRegionDataMap() override;

		// override (TESRegionData)
		Type               GetType() const override;
		void               ConstructSelf() override;
		void               Unk_05(void) override;
		void               CopyFrom(TESRegionData* a_src, bool a_copy) override;
		bool			   IsLoaded() const override;
	public:
		BSFixedString mapName;
	};
	static_assert(sizeof(TESRegionDataMap) == 0x18);
}
