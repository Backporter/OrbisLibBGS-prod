#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSIMusicType;

	struct BSMusicEvent
	{
	public:
		enum class MUSIC_MESSAGE_TYPE
		{
			kAdd,
			kRemove,
			kRemoveImmediate,
			kPause,
			kUnpause
		};
	public:
		BSIMusicType* musicType;
		int32_t		  msgType;
		uint32_t      pad0C;
	};
	static_assert(sizeof(BSMusicEvent) == 0x10);

}