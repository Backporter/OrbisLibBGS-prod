#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTSmartPointer.h"
#include "../S/StreamBase.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		class AsyncStream;

		enum class SeekMode
		{
			kSet = 0,
			kCur = 1,
			kEnd = 2
		};

		class Stream : public StreamBase
		{
		public:
			~Stream() override = default;
		};
	}
}