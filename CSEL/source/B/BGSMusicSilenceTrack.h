#pragma once

#include "../B/BGSMusicTrack.h"

namespace ConsoleRE
{
	class BGSMusicSilenceTrack : public BGSMusicTrack
	{
	public:
		~BGSMusicSilenceTrack() override;

		// override (BGSMusicTrack)
		void      DoUpdate(void) override;
		void      DoPlay() override;
		void      DoPause() override;
		void      DoFinish(bool a_arg1, float a_arg2) override;
		float     GetDurationImpl() const override;
		uint32_t  GetType() const override;
		void      Load(TESFile* a_mod) override;
	public:
		float			duration;
		uint32_t		pad20;
		uint32_t		playTime;
		uint32_t		pauseTime;
	};
	static_assert(sizeof(BGSMusicSilenceTrack) == 0x30);
}