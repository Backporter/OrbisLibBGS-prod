#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTList.h"
#include "../T/TESCondition.h"
#include "../T/TESDescription.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class BGSMenuIcon;
	class TESQuest;

	class BGSMessage : public TESForm, public TESFullName, public TESDescription
	{
	public:
		static constexpr int TypeID = 105;

		struct MESSAGEBOX_BUTTON
		{
		public:
			BSFixedString text;
			TESCondition  conditions;
		};
		static_assert(sizeof(MESSAGEBOX_BUTTON) == 0x10);
	public:
		~BGSMessage() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BGSMenuIcon*                                 icon;       
		TESQuest*                                    ownerQuest; 
		BSSimpleList<MESSAGEBOX_BUTTON*>             menuButtons;
		uint32_t									 flags;
		uint32_t									 displayTime;
	};
	static_assert(sizeof(BGSMessage) == 0x68);
}