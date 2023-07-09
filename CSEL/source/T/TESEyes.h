#pragma once

#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class TESEyes : public TESForm, public TESFullName, public TESTexture
	{
	public:
		static constexpr int TypeID = 13;
		
		~TESEyes() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
	public:
		uint8_t flags;
	};
	static_assert(sizeof(TESEyes) == 0x48);
}