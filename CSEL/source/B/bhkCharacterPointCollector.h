#pragma once

#include "../H/hkpAllCdPointCollector.h"

namespace ConsoleRE
{
	class bhkCharacterPointCollector : public hkpAllCdPointCollector
	{
	public:
		~bhkCharacterPointCollector() override;

		// override (hkpAllCdPointCollector)
		void AddCdPoint(const hkpCdPoint& a_point) override;
		void Reset() override;
	public:
		uint64_t unk220;
		uint64_t unk228;
		uint64_t unk230;
		uint64_t unk238;
	};
}