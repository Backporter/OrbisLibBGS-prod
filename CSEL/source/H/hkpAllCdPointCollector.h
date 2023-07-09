#pragma once

#include "../H/hkArray.h"
#include "../H/hkpCdPointCollector.h"
#include "../H/hkpRootCdPoint.h"

namespace ConsoleRE
{
	class hkpAllCdPointCollector : public hkpCdPointCollector
	{
	public:
		~hkpAllCdPointCollector() override;

		// override (hkpCdPointCollector)
		void AddCdPoint(const hkpCdPoint& a_point) override;
		void Reset() override;
	public:
		hkInplaceArray<hkpRootCdPoint, 8> hits;
	};
}