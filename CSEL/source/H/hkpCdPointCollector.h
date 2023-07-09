#pragma once

namespace ConsoleRE
{
	struct hkpCdPoint;

	class hkpCdPointCollector
	{
	public:
		virtual ~hkpCdPointCollector();

		// add
		virtual void AddCdPoint(const hkpCdPoint& a_point) = 0;
		virtual void Reset();
	public:
		float    earlyOutDistance;
	};
	static_assert(sizeof(hkpCdPointCollector) == 0x10);
}