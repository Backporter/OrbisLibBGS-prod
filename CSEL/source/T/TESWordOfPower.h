#pragma once

#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class TESWordOfPower : public TESForm, public TESFullName
	{
	public:
		static constexpr int TypeID = 118;
		
		~TESWordOfPower() override;

		// override (TESForm)
		bool Load(TESFile* a_mod) override;
	public:
		BSFixedString translation;
	};
	static_assert(sizeof(TESWordOfPower) == 0x38);
}