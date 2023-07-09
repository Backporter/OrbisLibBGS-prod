#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESDescription.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class BGSSkillPerkTreeNode;

	class ActorValueInfo : public TESForm, public TESFullName, public TESDescription
	{
	public:
		static constexpr int TypeID = 95;

		struct Skill
		{
			float useMult;
			float offsetMult;
			float inproveMult;
			float inproveOffset;
		};
		static_assert(sizeof(Skill) == 0x10);
	public:
		~ActorValueInfo() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		const char*			  enumName;
		BSFixedString		  abbreviation;
		uint32_t			  flags;
		uint32_t			  Unk054;
		uint64_t			  Unk058;
		uint32_t			  Unk060;
		uint32_t			  Unk064;
		uint32_t			  Unk068;
		uint32_t			  Unk06C;
		uint32_t			  Unk070;
		uint32_t			  Unk074;
		uint32_t			  Unk078;
		uint32_t			  Unk07C;
		uint32_t			  Unk080;
		uint32_t			  Unk084;
		uint32_t			  Unk088;
		uint32_t			  Unk08C;
		uint32_t			  Unk090;
		uint32_t			  Unk094;
		uint32_t			  Unk098;
		uint32_t			  Unk09C;
		uint64_t			  Unk0A0;
		uint64_t			  Unk0A8;
		uint64_t			  Unk0B0;
		uint64_t			  Unk0B8;
		uint64_t			  Unk0C0;
		uint64_t			  Unk0C8;
		uint64_t			  Unk0D0;
		uint64_t			  Unk0D8;
		uint64_t			  Unk0E0;
		uint64_t			  Unk0E8;
		uint64_t			  Unk0F0;
		Skill*				  skill;
		uint32_t			  Unk100;
		uint32_t			  Unk104;
		BGSSkillPerkTreeNode* perkTree;
		uint32_t			  Unk110;
		uint32_t			  Unk114;
	};
	static_assert(sizeof(ActorValueInfo) == 0x118);
}