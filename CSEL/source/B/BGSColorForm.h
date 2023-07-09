#pragma once

#include "../C/Color.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class BGSColorForm : public TESForm, public TESFullName
	{
	public:
		static constexpr int TypeID = 133;
	public:
		~BGSColorForm();

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
	public:
		Color			color;
		uint32_t		flags;
	};
	static_assert(sizeof(BGSColorForm) == 0x38);
}