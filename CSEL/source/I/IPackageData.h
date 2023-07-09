#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"

namespace ConsoleRE
{
	class BGSLoadFormBuffer;
	class TESFile;

	class IPackageData
	{
	public:
		virtual ~IPackageData();
	};
	static_assert(sizeof(IPackageData) == 0x8);
}