#pragma once

#include "../B/BGSEquipType.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../M/MagicItem.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESWeightForm.h"
#include "../T/TESValueForm.h"

namespace ConsoleRE
{
	class Data
	{
	public:
		int32_t  costOverride;
		uint32_t flags;
	};
	static_assert(sizeof(Data) == 0x8);
	
	struct GameData
	{
	public:
		uint16_t knownEffectFlags;
		uint16_t playerUses;
	};
	static_assert(sizeof(GameData) == 0x4);

	class IngredientItem :
		public MagicItem,
		public TESModelTextureSwap,
		public TESWeightForm,
		public BGSEquipType,
		public BGSDestructibleObjectForm,
		public BGSPickupPutdownSounds,
		public TESValueForm
	{
	public:
		static constexpr int TypeID = 30;
	public:
		~IngredientItem() override;
	public:
		Data          data;
		GameData      gamedata;
	};
	static_assert(sizeof(IngredientItem) == 0x118);
}