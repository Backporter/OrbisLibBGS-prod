#pragma once

#include "../N/NiPoint3.h"
#include "../N/NiAVObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	struct BSSoundHandle
	{
	public:
		enum : uint32_t
		{
			kInvalidID = static_cast<uint32_t>(-1)
		};

		enum class AssumedState
		{
			kInitialized = 0,
			kPlaying = 1,
			kStopped = 2,
			kPaused = 3
		};

		enum class LoopType
		{
			kNone = 0,
			kWholeFile = 1,
			kEnvFast = 2,
			kEnvSlow = 3
		};
	public:
		BSSoundHandle();
		~BSSoundHandle() = default;

		//
		bool	IsValid();
		bool    SetPosition(NiPoint3 a_pos);
		void    SetObjectToFollow(NiAVObject* a_node);
		bool    Stop();
		bool    Play();
	public:
		uint32_t	soundID;
		bool		assumeSuccess;
		uint8_t     pad05;
		uint16_t    pad06;
		uint32_t	state;
	};
	static_assert(sizeof(BSSoundHandle) == 0xC);
}