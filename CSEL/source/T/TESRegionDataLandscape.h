#pragma once

#include "../B/BSString.h"
#include "../T/TESRegionData.h"

namespace ConsoleRE
{
	class TESFile;
	class TESTexture;

	class TESRegionDataLandscape : public TESRegionData
	{
	public:
		~TESRegionDataLandscape() override;

		// override (TESRegionData)
		Type               GetType() const override;
		void               ConstructSelf() override;
		void               Unk_05(void) override;
		void               CopyFrom(TESRegionData* a_src, bool a_copy) override;
		bool			   IsLoaded() const override;

		// add
		virtual bool LoadIcon(TESFile* a_mod);
		virtual void GetIconFileName(BSString* a_dst);
		virtual bool SetIconFileName(BSString* a_name);
	public:
		TESTexture* icon;
	};
	static_assert(sizeof(TESRegionDataLandscape) == 0x18);
}
