#pragma once

#include "../B/BSAtomic.h"

namespace ConsoleRE
{
	class ActorPackageData;
	class TESPackage;

	class ActorPackage
	{
	public:
		mutable BSSpinLock									packageLock;
		TESPackage*											package;
		ActorPackageData*									data;
		int32_t												target;
		int32_t												currentProcedureIndex;
		float												packageStartTime;
		uint32_t											modifiedPackageFlag;
		uint16_t											modifiedInterruptFlag;
		int8_t												actorPackageFlags;
		int8_t												preferredSpeed;
		uint32_t											pad2C;
	};
}