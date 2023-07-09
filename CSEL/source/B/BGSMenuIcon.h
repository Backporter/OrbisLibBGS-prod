#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSMenuIcon : public TESForm
	{
	public:
		static constexpr int TypeID = 8;
	public:
		~BGSMenuIcon() override;

		// override (TESForm)
		bool Load(TESFile* a_mod) override;
	public:
	};
	static_assert(sizeof(BGSMenuIcon) == 0x20);
}