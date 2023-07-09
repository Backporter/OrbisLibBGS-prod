#pragma once

#include "../T/TESForm.h"
#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class BGSKeyword : public TESForm
	{
	public:
		static constexpr int TypeID = 4;

		~BGSKeyword() override;
	public:
		BSFixedString keyword;
	};
}