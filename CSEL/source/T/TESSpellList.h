#pragma once

#include "../B/BaseFormComponent.h"
#include <stdint.h>

namespace ConsoleRE
{
	class SpellItem;
	class TESLevSpell;
	class TESShout;

	class TESSpellList : BaseFormComponent
	{
	public:
		struct SpellData
		{
			SpellData() = default;
			~SpellData() = default;
		public:
			SpellItem**		spells { 0 };
			TESLevSpell**	levSpells { 0 };
			TESShout**		shouts { 0 };
			uint32_t		numSpells { 0 };
			uint32_t		numlevSpells { 0 };
			uint32_t		numShouts { 0 };
		};
		static_assert(sizeof(SpellData) == 0x28);
	public:
		~TESSpellList();

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		//
		uint32_t	GetSpellCount();
		uint32_t	GetShoutCount();
		bool		GetSpell(uint32_t val, SpellItem*& out);
		bool		GetShout(uint32_t val, TESShout*& out);
		SpellItem*	GetSpell(uint32_t val);
		TESShout*	GetShout(uint32_t val);
	public:
		SpellData* actorEffects;
	};
}