#pragma once
#include "../A/ArchiveStream.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		class CompressedArchiveStream : public ArchiveStream
		{
		public:
			CompressedArchiveStream();
			virtual ~CompressedArchiveStream();
		};
	}
}