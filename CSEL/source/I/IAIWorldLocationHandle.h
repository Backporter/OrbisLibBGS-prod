#pragma once

namespace ConsoleRE
{
	class IAIWorldLocation;
	class PackageLocation;
	class TESObjectREFR;
	struct AIWorldLocationContext;

	class IAIWorldLocationHandle
	{
	public:
		virtual ~IAIWorldLocationHandle();

		// add
		virtual const IAIWorldLocation* AllocateLocation(AIWorldLocationContext* a_context) = 0;
		virtual PackageLocation*        GetAsPackageLocation();
		virtual bool                    IsRefAtLocation(AIWorldLocationContext* a_context, TESObjectREFR* a_ref) = 0;
	};
	static_assert(sizeof(IAIWorldLocationHandle) == 0x8);
}
