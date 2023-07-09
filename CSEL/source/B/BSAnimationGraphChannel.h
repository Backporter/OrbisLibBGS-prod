#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	class BSAnimationGraphChannel : public BSIntrusiveRefCounted
	{
	public:
		virtual ~BSAnimationGraphChannel();

		// add
		virtual void PollChannelUpdateImpl(bool a_arg1) = 0;
		virtual void ResetImpl() = 0;
	public:
		uint32_t			pad0C;
		const BSFixedString channelName;
		uint32_t			value;
		uint32_t			pad1C;
	};
	static_assert(sizeof(BSAnimationGraphChannel) == 0x20);
}