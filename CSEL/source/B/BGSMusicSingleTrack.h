#pragma once

#include "../B/BGSMusicTrack.h"
#include "../B/BSSoundHandle.h"
#include "../B/BSTArray.h"
#include "../I/ID.h"

namespace ConsoleRE
{
	class BGSMusicSingleTrack : public BGSMusicTrack
	{
	public:
		struct LoopData
		{
			float			loopBegin;
			float			loopEnd;
			uint32_t		loopCount;
		};
		static_assert(sizeof(LoopData) == 0xC);
	public:
		~BGSMusicSingleTrack() override;

		// override (BGSMusicTrack)
		void      DoUpdate() override;
		void      DoPlay() override;
		void      DoPause() override;
		void      DoFinish(bool a_arg1, float a_arg2) override;
		float     GetDurationImpl() const override;
		uint32_t  GetType() const override;
		void      DoSetDuckingAttenuation(uint16_t a_val) override;
		void      DoClearDucking() override;
		void      Load(TESFile* a_mod) override;
	public:
		BSResource::ID  trackID;
		BSResource::ID  finaleID;
		BSTArray<float> cuePoints;
		uint32_t		nextCuePoint;
		uint32_t		loopsRemaining;
		uint32_t		lastKnownPlaybackPosition;
		uint32_t		pad5C;
		LoopData*       loopData;
		BSSoundHandle   trackHandle;
		BSSoundHandle   finaleHandle;
	};
	static_assert(sizeof(BGSMusicSingleTrack) == 0x78);
}