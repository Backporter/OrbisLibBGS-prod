#pragma once

#include "../B/bhkWorldObject.h"

namespace ConsoleRE
{
	class bhkPhantom : public bhkWorldObject
	{
	public:
		~bhkPhantom() override;

		// override (bhkWorldObject)
		const NiRTTI* GetRTTI() const override;
	public:
		uint64_t unk28;
	};
	static_assert(sizeof(bhkPhantom) == 0x30);
}