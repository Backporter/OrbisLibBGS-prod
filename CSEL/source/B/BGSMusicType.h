#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIMusicType.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSMusicType : public TESForm, public BSIMusicType 
	{
	public:
		static constexpr int TypeID = 109;
	public:
		~BGSMusicType() override;
		
		// override (TESForm)
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;

		// override (BSIMusicType)
		void DoUpdate() override;
		void DoPlay() override;
		void DoPause() override;
		void DoFinish(bool a_arg1) override;
		void DoApplyDuckingAttenuation(uint16_t a_arg1) override;
		void DoClearDucking() override;
		void DoPrepare() override;
	public:
		BSFixedString formEditorID;
	};
	static_assert(sizeof(BGSMusicType) == 0x68);
}