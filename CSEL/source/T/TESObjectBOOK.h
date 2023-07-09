#pragma once

#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"
#include "../T/TESDescription.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../B/BGSKeywordForm.h"
#include "../T/TESObjectSTAT.h"
#include "../S/SpellItem.h"

namespace ConsoleRE
{
	struct OBJ_BOOK
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kAdvancesActorValue = 1 << 0,
			kCantTake = 1 << 1,
			kTeachesSpell = 1 << 2,
			kHasBeenRead = 1 << 3
		};

		enum class Type
		{
			kBookTome = 0x00,
			kNoteScroll = -1,
		};

		union Teaches
		{
			uint32_t	actorValueToAdvance;
			SpellItem*	spell;
		};
		static_assert(sizeof(Teaches) == 0x8);
	public:
		uint32_t GetSanitizedType()
		{
			if ((flags & 4) == 4)
			{
				return 4;
			}
			else if ((flags & 1) == 1)
			{
				return 1;
			}

			return 0;
		}
	public:
		uint8_t	 flags;
		uint8_t	 type;
		uint16_t pad02;
		uint32_t pad04;
		Teaches  teaches;
	};
	static_assert(sizeof(OBJ_BOOK) == 0x10);

	class TESObjectBOOK : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESValueForm, public TESWeightForm, public TESDescription, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds, public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 27;

		~TESObjectBOOK() override;
	
		// override (TESBoundObject)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		bool GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;

		//
		bool       TeachesSkill() { return (data.flags & 1) == 1; }
		bool       TeachesSpell() { return (data.flags & 4) == 4; }
		bool       IsRead() { return (data.flags & 8) == 8; }
		bool       CanBeTaken() { return (data.flags & 2) == 2; }
	public:
		OBJ_BOOK		data;
		TESObjectSTAT*	inventoryModel;
		TESDescription	itemCardDescription;
	};
	static_assert(sizeof(TESObjectBOOK) == 0x108, "#");
}