#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../F/FormTypes.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class NiFormArray;

	struct IDLE_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kParent = 1 << 0,
			kSequence = 1 << 1,
			kNoAttacking = 1 << 2,
			kBlocking = 1 << 3
		};
	public:
		int8_t                          loopMin;
		int8_t                          loopMax;
		uint8_t							flags;
		uint8_t                         animationGroupSelection;
		uint16_t                        replayDelay;
	};
	static_assert(sizeof(IDLE_DATA) == 0x6);

	class TESIdleForm : public TESForm
	{
	public:
		static constexpr int TypeID = 78;
	public:
		~TESIdleForm() override;
		
		// override (TESForm)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		TESForm*    CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;
		void        InitItemImpl() override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
	public:
		TESCondition	conditions;
		IDLE_DATA		data;
		uint16_t		pad2E;
		NiFormArray*	childIdles;
		TESIdleForm*	parentIdle;
		TESIdleForm*	prevIdle;
		BSFixedString	animFileName;
		BSFixedString	animEventName;
		BSString		formEditorID;
	};
	static_assert(sizeof(TESIdleForm) == 0x68);
}