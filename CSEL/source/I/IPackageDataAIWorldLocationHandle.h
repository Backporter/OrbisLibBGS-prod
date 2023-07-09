#pragma once

#include "../I/IAIWorldLocationHandle.h"
#include "../I/IPackageData.h"

namespace ConsoleRE
{
	class IPackageDataAIWorldLocationHandle : public IAIWorldLocationHandle, public IPackageData
	{
	public:
		~IPackageDataAIWorldLocationHandle() override;
	};
	static_assert(sizeof(IPackageDataAIWorldLocationHandle) == 0x10);
}