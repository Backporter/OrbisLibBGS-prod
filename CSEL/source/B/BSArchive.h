#pragma once

#include "../B/BSArchiveHeader.h"

namespace ConsoleRE
{
	struct BSDirectoryEntry;

	class BSArchive : public BSArchiveHeader
	{
	public:
		uint32_t			pad24;
		BSDirectoryEntry*	directories;
	};
	static_assert(sizeof(BSArchive) == 0x30);
}