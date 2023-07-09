#pragma once

#include "../B/BGSAttackData.h"
#include "../B/BSTHashMap.h"
#include "../F/FormTypes.h"
#include "../N/NiRefObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BGSAttackDataMap : public NiRefObject
	{
	public:
		~BGSAttackDataMap() override;
	public:
		BSTHashMap<BSFixedString, NiPointer<BGSAttackData>> attackDataMap;
		TESRace*                                            defaultDataRace;
	};
}