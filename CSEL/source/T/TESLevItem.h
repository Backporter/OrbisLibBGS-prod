#pragma once

#include "../T/TESBoundObject.h"
#include "../T/TESLeveledList.h"

namespace ConsoleRE
{
	class TESLevItem : public TESBoundObject, public TESLeveledList
	{
	public:
		static constexpr int TypeID = 53;
	public:
		~TESLevItem() override;

		// override (TESBoundObject)
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;

		// override (TESLeveledList)
		int32_t			GetLevDifferenceMax() override;
		bool			GetCanContainFormsOfType(uint32_t a_type) const override;
	public:
	};
	static_assert(sizeof(TESLevItem) == 0x50);
}