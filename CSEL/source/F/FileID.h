#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSResource
	{
		struct FileID
		{
		public:
			uint32_t		file;
			char			ext[4];
		};
		static_assert(sizeof(FileID) == 0x8);
	}
}