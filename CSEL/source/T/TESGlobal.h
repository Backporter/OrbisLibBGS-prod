#pragma once

#include "../B/BSString.h"
#include "../T/TESForm.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESGlobal : public TESForm
	{
	public:
		static constexpr int TypeID = 9;
	public:
		~TESGlobal() override;

		// override (TESform)
		bool        Load(TESFile* a_mod) override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
	public:
		BSString                             formEditorID;
		uint8_t								 type;
		uint8_t								 pad31;
		uint16_t							 pad32;
		float                                value;
	};
	static_assert(sizeof(TESGlobal) == 0x38);
}