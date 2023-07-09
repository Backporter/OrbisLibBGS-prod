#pragma once

#include "../T/TESForm.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class TESObjectANIO : public TESForm, public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 83;
		
		~TESObjectANIO() override;

		// override (TESForm)
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
	public:
		BSFixedString formEditorID;
		BSFixedString unloadEventName;
	};
	static_assert(sizeof(TESObjectANIO) == 0x68);
}