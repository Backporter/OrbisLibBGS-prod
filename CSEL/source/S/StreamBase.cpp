#include "../S/StreamBase.h"

#include <atomic>

namespace ConsoleRE
{
	namespace BSResource
	{
		StreamBase::StreamBase() :
			totalSize(0),
			flags(0)
		{}

		StreamBase::StreamBase(uint32_t a_totalSize) :
			totalSize(a_totalSize),
			flags(0)
		{}

		uint64_t StreamBase::DoGetKey() const
		{
			return 0;
		}

		ErrorCode StreamBase::DoGetInfo(Info&)
		{
			return ErrorCode::kUnsupported;
		}

		uint32_t StreamBase::DecRef()
		{
			std::atomic<uint32_t> myFlags { flags };
			uint32_t expected;

			do 
			{
				expected = myFlags;
			} 
			while (!myFlags.compare_exchange_weak(expected, expected - kRefCountBeg));

			return (expected - kRefCountBeg) & kRefCountMask;

		}

		uint32_t StreamBase::IncRef()
		{
			std::atomic<uint32_t> myFlags{ flags };
			uint32_t expected;

			do 
			{
				expected = myFlags;
			} 
			while (!myFlags.compare_exchange_weak(expected, expected + kRefCountBeg));

			return (expected - kRefCountBeg) & kRefCountMask;
		}

		bool StreamBase::IsWritable() const
		{
			return static_cast<bool>(flags & kWritable);
		}
	}
}