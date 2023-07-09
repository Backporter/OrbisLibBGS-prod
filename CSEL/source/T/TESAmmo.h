#pragma once

#include "../B/BSFixedString.h"
#include "../B/BGSProjectile.h"
#include "../T/TESFullName.h"
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../T/TESDescription.h"
#include "../B/BGSKeywordForm.h"

namespace ConsoleRE
{
	struct AMMO_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kIgnoresNormalWeaponResistance = 1 << 0,
			kNonPlayable = 1 << 1,
			kNonBolt = 1 << 2
		};
	public:
		BGSProjectile*							projectile;
		uint8_t									flags;
		uint8_t									pa09;
		uint16_t								pa0A;
		float									damage;
	};
	static_assert(sizeof(AMMO_DATA) == 0x10);

	class TESAmmo : 
		public TESBoundObject, 
		public TESFullName, 
		public TESModelTextureSwap, 
		public TESValueForm, 
		public TESWeightForm, 
		public BGSDestructibleObjectForm, 
		public BGSPickupPutdownSounds, 
		public TESDescription, 
		public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 42;
	public:
		~TESAmmo() override;

		// override (TESBoundObject)
		void        InitializeData() override;
		bool        Load(TESFile* a_mod) override;
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;
		void        InitItemImpl() override;
		bool        GetPlayable() const override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref, bool a_arg3) override;
		void        HandleRemoveItemFromContainer(TESObjectREFR* a_container) override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;

		bool isBolt()     { return (data.flags & 4) != 4; }
		bool isPlayable() { return (data.flags & 2) != 2; }
	public:
		AMMO_DATA     data;
		BSFixedString shortDesc;
	};
	static_assert(sizeof(TESAmmo) == 0xF8);
}