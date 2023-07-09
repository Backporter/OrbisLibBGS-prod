#pragma once

#include "../B/BGSPackageDataPointerTemplate.h"
#include "../I/IPackageDataAIWorldLocationHandle.h"

namespace ConsoleRE
{
	class PackageLocation;

	class BGSPackageDataLocation : public BGSPackageDataPointerTemplate<IPackageDataAIWorldLocationHandle, PackageLocation>
	{
	public:
		~BGSPackageDataLocation() override;
	};
}