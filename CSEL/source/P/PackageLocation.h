#pragma once

#include "../I/IAIWorldLocationHandle.h"

namespace ConsoleRE
{
	class PackageLocation : public IAIWorldLocationHandle
	{
	public:
		~PackageLocation() override;

		// override (IAIWorldLocationHandle)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext* a_context) override;
		PackageLocation*        GetAsPackageLocation() override;
		bool                    IsRefAtLocation(AIWorldLocationContext* a_context, TESObjectREFR* a_ref) override;
	public:
	};
}