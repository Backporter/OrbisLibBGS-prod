#pragma once

#include "../B/bhkShape.h"

namespace ConsoleRE
{
	class bhkShapeCollection : public bhkShape
	{
	public:
		~bhkShapeCollection() override;

		// override (bhkShape)
		const NiRTTI* GetRTTI() const override;
	};
	static_assert(sizeof(bhkShapeCollection) == 0x28);
}