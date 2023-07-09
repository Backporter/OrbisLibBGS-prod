#pragma once

#include "../B/BGSMusicTrack.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BGSMusicPaletteTrack : public BGSMusicTrack
	{
	public:
		~BGSMusicPaletteTrack() override;

		// override (BGSMusicTrack)
		void      DoUpdate() override;
		void      DoPlay() override;
		void      DoPause() override;
		void      DoFinish(bool a_arg1, float a_arg2) override;
		float     GetDurationImpl() const override;
		uint32_t  GetType() const override;
		void      InitItem(TESForm* a_form) override;
		void      Load(TESFile* a_mod) override;
	public:
		BSTArray<BSIMusicTrack*> layers[3];
		int32_t					 playingIndexes[3];
		float                    duration;
		float                    fadeOutTime;
	};
}