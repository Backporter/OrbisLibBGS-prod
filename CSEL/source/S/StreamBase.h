#pragma once

#include "../E/ErrorCodes.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSResource
	{
		struct Info;

		class StreamBase
		{
		public:
			enum : uint32_t
			{
				kWritable = 1 << 0,
				kRefCountBeg = 0x1000,
				kRefCountMask = static_cast<uint32_t>(0xFFFFF000),
			};
		public:
			StreamBase();
			StreamBase(uint32_t a_totalSize);
			virtual ~StreamBase() = default;

			// add
			virtual ErrorCode                   DoOpen() = 0;
			virtual void                        DoClose() = 0;
			virtual uint64_t					DoGetKey() const;
			virtual ErrorCode                   DoGetInfo(Info& a_info);

			uint32_t		DecRef();
			uint32_t		IncRef();
			bool			IsWritable() const;
		public:
			uint32_t totalSize;
			uint32_t flags;
		};
	}
}
