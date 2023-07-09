#pragma once

#include "../B/BGSPerkEntry.h"
#include "../S/SpellItem.h"

namespace ConsoleRE
{
	// 0x18
	class BGSAbilityPerkEntry : public BGSPerkEntry
	{
	public:
		BGSAbilityPerkEntry();
		virtual ~BGSAbilityPerkEntry();
	public:
		SpellItem* Unk10;
	};
}