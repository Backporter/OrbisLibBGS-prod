#pragma once

#include "../T/TESObjectMISC.h"
#include "../T/TESQualityForm.h"
#include "../T/TESDescription.h"

namespace ConsoleRE
{
	// 0xF0
	class BGSApparatus :
		public TESObjectMISC,
		public TESQualityForm,
		public TESDescription
	{
	public:
		static constexpr int TypeID = 33;
	public:
		~BGSApparatus() override;

		// override (TESObjectMISC)
		bool Load(TESFile* a_mod) override;
	};
	static_assert(sizeof(BGSApparatus) == 0xF0);
}