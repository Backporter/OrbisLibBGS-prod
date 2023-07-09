#pragma once

#include "../B/BSTArray.h"

#include <functional>
#include <stdint.h>

namespace ConsoleRE
{
	class ActorValueInfo;
	class BGSPerk;

	// 0x58
	class BGSSkillPerkTreeNode
	{
	public:
		virtual ~BGSSkillPerkTreeNode();

		bool Visit(std::function<bool(BGSPerk*)> a_func)
		{
			if (a_func(perk))
				return true;

			for (uint32_t i = 0; i < children.size(); i++)
			{
				BGSSkillPerkTreeNode* s_node = NULL;
				children.Get(i, s_node);

				if (s_node->Visit(a_func))
					return true;
			}

			return false;
		}
	public:
		uint32_t						index;
		uint32_t						Unk0C;             
		BSTArray<BGSSkillPerkTreeNode*> children;
		BSTArray<BGSSkillPerkTreeNode*> parents;
		BGSPerk*                        perk;
		uint32_t						Unk38;             
		uint32_t						perkGridX;
		uint32_t						perkGridY;
		uint32_t						Unk44;
		ActorValueInfo*                 associatedSkill;
		float                           horizontalPosition;
		float                           verticalPosition;
	};
	static_assert(sizeof(BGSSkillPerkTreeNode) == 0x58);
}