#pragma once

#include "../F/FileID.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		struct ID : public FileID
		{
		public:
			uint32_t dir;
		};
		static_assert(sizeof(ID) == 0xC);
	}
}