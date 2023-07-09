#pragma once

#include "../F/FormTypes.h"
#include "../T/TESObjectMISC.h"

namespace ConsoleRE
{
	class TESKey : public TESObjectMISC
	{
	public:
		static constexpr int TypeID = 45;
	public:
		~TESKey() override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;
	};
	static_assert(sizeof(TESKey) == 0xD0);
}