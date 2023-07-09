#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSFootstep : public TESForm
	{
	public:
		static constexpr int TypeID = 110;

		~BGSFootstep() override;
	public:
		BSFixedString     tag;
		BGSImpactDataSet* impactSet;
	};
}