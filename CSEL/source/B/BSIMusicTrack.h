#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSIMusicTrack
	{
	public:
		virtual ~BSIMusicTrack();

		// add
		virtual void                       DoUpdate() = 0;
		virtual void                       DoPlay() = 0;
		virtual void                       DoPause() = 0;
		virtual void                       DoFinish(bool a_immediate, float a_fadeTime) = 0;
		virtual float					   GetDurationImpl() const = 0;
		virtual uint32_t				   GetType() const = 0;
		virtual bool					   TestCanPlay() const;
		virtual uint32_t				   GetMusicStatus() const;
		virtual void                       DoSetDuckingAttenuation(uint16_t a_ducking);
		virtual void                       DoClearDucking();
	public:
		uint32_t trackStatus;
		uint32_t pad0C;
	};
	static_assert(sizeof(BSIMusicTrack) == 0x10);
}