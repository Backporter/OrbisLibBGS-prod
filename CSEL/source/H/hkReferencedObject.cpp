#include "../H/hkReferencedObject.h"

namespace ConsoleRE
{
	hkClass* hkReferencedObject::GetClassType() const
	{
		return nullptr;
	}

	void hkReferencedObject::CalcContentStatistics(hkStatisticsCollector*, const hkClass*) const
	{
		return;
	}

}