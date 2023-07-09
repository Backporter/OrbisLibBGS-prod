#pragma once

#include "../H/hkBaseObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	class hkClass;
	class hkStatisticsCollector;

	class hkReferencedObject : public hkBaseObject
	{
	public:
		hkReferencedObject() = default;
		~hkReferencedObject() override = default;

		// add
		virtual hkClass*			GetClassType() const;
		virtual void				CalcContentStatistics(hkStatisticsCollector* , const hkClass*) const;
	public:
		uint16_t					memSizeAndFlags;
		volatile mutable int16_t	referenceCount;
	};
	static_assert(sizeof(hkReferencedObject) == 0x10);
}