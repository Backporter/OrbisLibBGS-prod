#pragma once

#include "../B/bhkPhantom.h"

namespace ConsoleRE
{
	class bhkShapePhantom : public bhkPhantom
	{
	public:
		~bhkShapePhantom() override;

		// override (bhkPhantom)
		const NiRTTI* GetRTTI() const override;
		void          LinkObject(NiStream& a_stream) override;
	};
	static_assert(sizeof(bhkShapePhantom) == 0x30);

}