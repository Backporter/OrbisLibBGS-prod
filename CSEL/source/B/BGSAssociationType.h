#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSAssociationType : public TESForm
	{
	public:
		static constexpr int TypeID = 123;
	public:		
		~BGSAssociationType() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
	public:
		BSFixedString		associationLabels[2][2];
		uint32_t			flags;
	};
	static_assert(sizeof(BGSAssociationType) == 0x48);
}