#pragma once

#include "../B/BSFixedString.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	struct DIALOGUE_DATA
	{
	public:
		uint8_t		topicFlags;
		uint8_t		type;
		uint16_t	subtype;
	};

	class TESTopic : public TESForm, public TESFullName
	{
	public:
		static constexpr int TypeID = 75;
	public:
		~TESTopic() override;

		// override (TESForm)
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
		bool        IsParentForm() override;
		bool        IsFormTypeChild(uint32_t a_type) override;

		// override (TESFullName)
		uint32_t    GetFullNameLength() override;
		const char* GetFullName() override;

		//
		float GetPriority() { return static_cast<float>(priorityAndJournalIndex >> (8 * 3)); }
	public:
		DIALOGUE_DATA		data;
		uint32_t			priorityAndJournalIndex;
		BGSDialogueBranch*	ownerBranch;
		TESQuest*			ownerQuest;
		TESTopicInfo**		topicInfos;
		uint32_t			numTopicInfos;
		uint32_t			firstFileOffset;
		BSFixedString		formEditorID;
	};
	static_assert(sizeof(TESTopic) == 0x60);

}