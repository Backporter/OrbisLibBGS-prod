#pragma once

#include "../B/BSTArray.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSStoryManagerBranchNode;
	class BGSStoryManagerQuestNode;
	class BGSStoryManagerTreeForm;
	class PeriodicUpdateTimer;
	class TESCondition;
	class TESQuest;

	class BGSStoryManagerTreeVisitor
	{
	public:
		enum class VisitControl
		{ 
		};
	public:
		virtual ~BGSStoryManagerTreeVisitor();

		// add
		virtual VisitControl VisitBranchNode(BGSStoryManagerBranchNode& a_node);
		virtual VisitControl VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_arg2);
		virtual VisitControl VisitQuest(TESQuest& a_quest);
		virtual void         Revert();
	public:
		PeriodicUpdateTimer*				timer;
		int32_t								currentCursorDepth;
		uint32_t							pad14;
		BGSStoryManagerQuestNode*			lastQuestParent;
		BSTArray<BGSStoryManagerTreeForm*>	cursorAncestry;
		uint32_t							queryID; 
	};
	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x38);

	class BGSStoryManagerTreeForm : public TESForm
	{
	public:
		~BGSStoryManagerTreeForm() override;
		
		// add
		virtual uint32_t								 QChildCount();
		virtual BGSStoryManagerTreeForm*				 GetChild(uint32_t a_idx);
		virtual TESCondition*							 QConditions() = 0;
		virtual BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) = 0;
	public:
		uint32_t lastVisitorID;
	};
	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x20);
}