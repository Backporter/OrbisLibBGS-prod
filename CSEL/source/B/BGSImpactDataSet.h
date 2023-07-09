#pragma once

#include "../T/TESForm.h"
#include "../B/BGSPreloadable.h"

namespace ConsoleRE
{
	class BGSImpactDataSet : public TESForm, public BGSPreloadable
	{
	public:
		static constexpr int TypeID = 101;
	public:
	};
}