#pragma once

#include "../T/TESBoundObject.h"

namespace ConsoleRE
{
	class TESBoundAnimObject : public TESBoundObject
	{
	public:
		~TESBoundAnimObject() override;

		// override (TESBoundObject)
		bool IsBoundAnimObject() override;
		bool ReplaceModel(const char* a_str) override;
	};
	static_assert(sizeof(TESBoundAnimObject) == 0x28);
}