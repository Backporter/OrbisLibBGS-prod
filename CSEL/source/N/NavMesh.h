#pragma once

#include "../B/BSNavmesh.h"
#include "../T/TESChildCell.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class NavMesh : public TESForm, public TESChildCell, public BSNavmesh
	{
	public:
		static constexpr int TypeID = 73;
	public:
		~NavMesh() override;

		// override (TESForm)
		bool Load(TESFile* a_mod) override;
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		void GetFormDetailedString(char* a_buf, uint32_t a_bufLen) override;
		void SetDelete(bool a_set) override;
		void SetAltered(bool a_set) override;
		bool BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;
		void CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;

		// add
		virtual void Save();
		virtual bool SavesBefore(FORM* a_form);
		virtual bool SavesBefore(TESForm* a_form);
		virtual bool ProcessBeforeSave();
	};
	static_assert(sizeof(NavMesh) == 0x100);
}