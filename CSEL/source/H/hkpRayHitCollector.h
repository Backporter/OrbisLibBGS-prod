#pragma once
#include "hkpCdBody.h"
#include "hkpShapeRayCastCollectorOutput.h"

namespace ConsoleRE
{
	class hkpRayHitCollector
	{
	public:
		virtual void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) = 0;  // 00
		virtual ~hkpRayHitCollector();
	public:
		float         earlyOutHitFraction{ 1.0f };
	};
}