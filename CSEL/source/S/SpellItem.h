#pragma once
#include "../M/MagicItem.h"
#include "../B/BGSEquipType.h"
#include "../B/BGSMenuDisplayObject.h"
#include "../T/TESDescription.h"
#include "../B/BGSPerk.h"

namespace ConsoleRE
{
	class SpellItem : public MagicItem,  public BGSEquipType,  public BGSMenuDisplayObject,  public TESDescription
	{
	public:
		static constexpr int TypeID = 22;
		virtual ~SpellItem();
	public:
		uint32_t GetDelivery() { return delivery; }
	public:
		uint32_t costOverride;
		uint32_t flags;
		uint32_t spellType;
		float    chargeTime;
		uint32_t castingType;
		uint32_t delivery;
		float	 castDuration;
		float	 range;
		BGSPerk* castingPerk;
	};
	static_assert(sizeof(SpellItem) == 0xD8, "#");
}