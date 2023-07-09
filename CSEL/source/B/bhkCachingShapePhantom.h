#pragma once

#include "../B/bhkShapePhantom.h"

namespace ConsoleRE
{
	class bhkCachingShapePhantom : public bhkShapePhantom
	{
	public:
		~bhkCachingShapePhantom() override;

		// override (bhkShapePhantom)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
	};
	static_assert(sizeof(bhkCachingShapePhantom) == 0x30);
}