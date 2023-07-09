#pragma once

#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BSIMusicTrack;

	class BSIMusicType
	{
	public:
		virtual void DoUpdate() = 0;
		virtual void DoPlay() = 0;
		virtual void DoPause() = 0;
		virtual void DoFinish(bool a_arg1) = 0;
		virtual void DoApplyDuckingAttenuation(uint16_t a_ducking);
		virtual void DoClearDucking();
		virtual void DoPrepare();

		virtual ~BSIMusicType();
	public:
		uint32_t								 flags;
		uint8_t                                  priority;
		uint8_t                                  padding;
		uint16_t                                 ducksOtherMusicBy;
		float                                    fadeTime;
		uint32_t                                 currentTrackIndex;
		BSTArray<uint32_t>                       trackHistory;
		BSTArray<BSIMusicTrack*>                 tracks;
		uint32_t								 typeStatus;
	};
	static_assert(sizeof(BSIMusicType) == 0x40);
}