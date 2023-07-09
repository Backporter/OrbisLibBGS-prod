#pragma once

#include "../B/BSTArray.h"
#include "../T/TESRegionData.h"

namespace ConsoleRE
{
	class BGSMusicType;
	class BGSSoundDescriptorForm;
	class TESFile;

	class TESRegionDataSound : public TESRegionData
	{
	public:
		struct Sound
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kPleasant = 1 << 0,
				kCloudy = 1 << 1,
				kRainy = 1 << 2,
				kSnowy = 1 << 3
			};
		public:
			BGSSoundDescriptorForm*					sound;
			uint32_t								flags;
			float									chance;
		};
		static_assert(sizeof(Sound) == 0x10);
	public:
		~TESRegionDataSound() override;

		// override (TESRegionData)
		void               LoadData(TESForm* a_form) override;
		Type               GetType() const override;
		void               ConstructSelf() override;
		void               Unk_05(void) override;
		void               CopyFrom(TESRegionData* a_src, bool a_copy) override;
		bool			   IsLoaded() const override;

		// add
		virtual void Load(TESFile* a_mod);

	public:
		BGSMusicType*    music;
		BSTArray<Sound*> sounds;
	};
	static_assert(sizeof(TESRegionDataSound) == 0x30);
}
