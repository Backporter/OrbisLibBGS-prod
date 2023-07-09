#pragma once

#include "../B/BGSKeywordForm.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTTuple.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class QueuedPromoteLocationReferencesTask;

	struct UnloadedRefData
	{
	public:
		union CellKey
		{
			BSTTuple<int16_t, int16_t>	xy;
			uint32_t					raw;
		};
		static_assert(sizeof(CellKey) == 0x4);
	public:
		uint32_t	refID;
		uint32_t	parentSpaceID;
		CellKey		cellKey;
	};
	static_assert(sizeof(UnloadedRefData) == 0xC);

	struct SpecialRefData
	{
	public:
		BGSLocationRefType* type;
		UnloadedRefData     refData;
		uint32_t			pad14;
	};
	static_assert(sizeof(SpecialRefData) == 0x18);

	struct UniqueNPCData
	{
	public:
		Actor*			actor;
		uint32_t        refID;
		uint32_t		pad0C;
		BGSLocation*	editorLoc;
	};
	static_assert(sizeof(UniqueNPCData) == 0x18);

	struct OverrideData
	{
	public:
		BSTArray<UnloadedRefData>	 addedData;
		BSTHashMap<UnkKey, UnkValue> removedData;
	};
	static_assert(sizeof(OverrideData) == 0x30);

	class BGSLocation : public TESForm, public TESFullName, public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 104;

		struct KEYWORD_DATA
		{
		public:
			BGSKeyword*		keyword;
			float			data;
			uint32_t		pad0C;
		};
		static_assert(sizeof(KEYWORD_DATA) == 0x10);
	public:
		~BGSLocation() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		bool FindInFileFast(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
	public:
		BGSLocation*									parentLoc;
		TESFaction*										unreportedCrimeFaction;
		BGSMusicType*									musicType;
		uint32_t										worldLocMarker;
		float											worldLocRadius;
		uint32_t										horseLocMarker;
		uint32_t										pad6C;
		BSTArray<SpecialRefData>						specialRefs;
		BSTArray<UniqueNPCData>							uniqueNPCs;
		OverrideData*									overrideData;
		NiPointer<QueuedPromoteLocationReferencesTask>	promoteRefsTask;
		BSTArray<uint32_t>								promotedRefs;
		volatile int32_t								loadedCount;
		uint32_t										fileOffset;
		BSTArray<KEYWORD_DATA>							keywordData;
		uint32_t										lastChecked;
		bool											cleared;
		bool											everCleared;
		uint16_t										padCE;
	};
	static_assert(sizeof(BGSLocation) == 0xD0);
}