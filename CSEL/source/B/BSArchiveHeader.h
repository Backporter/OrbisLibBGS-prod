#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSArchiveHeader
	{
	public:
		struct ArchiveFlag
		{
		public:
			uint32_t flag;
		};
		static_assert(sizeof(ArchiveFlag) == 0x4);
	public:
		uint32_t	tag;
		uint32_t	version;
		uint32_t	headerSize;
		ArchiveFlag	flags;
		uint32_t	directories;
		uint32_t	files;
		uint32_t	directoryNamesLength;
		uint32_t	fileNamesLength;
		uint16_t	archiveType;
		uint16_t	pad22;
	};
	static_assert(sizeof(BSArchiveHeader) == 0x24);
}