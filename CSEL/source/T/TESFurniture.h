#pragma once

#include "../B/BSTArray.h"
#include "../F/FormTypes.h"
#include "../T/TESObjectACTI.h"

namespace ConsoleRE
{
	class TESFurniture : public TESObjectACTI
	{
	public:
		struct WorkBenchData
		{
		public:
			enum class BenchType
			{
				kNone = 0,
				kCreateObject = 1,
				kSmithingWeapon = 2,
				kEnchanting = 3,
				kEnchantingExperiment = 4,
				kAlchemy = 5,
				kAlchemyExperiment = 6,
				kSmithingArmor = 7,
			};
		public:
			uint8_t  benchType;
			uint8_t usesSkill;
		};
		static_assert(sizeof(WorkBenchData) == 0x2);

		struct EntryPointData
		{
		public:
			struct DisabledEntryPoint
			{
			public:
				enum class DisabledPoint
				{
					kNone = 0,
					kFront = 1 << 0,
					kBehind = 1 << 1,
					kRight = 1 << 2,
					kLeft = 1 << 3,
					kUp = 1 << 4
				};
			public:
				uint16_t									unk0;
				uint16_t									disabledPoints;
			};
			static_assert(sizeof(DisabledEntryPoint) == 0x4);
		public:
			uint32_t			entryPoint;
			DisabledEntryPoint	disabledEntryPoints;
			BGSKeyword*			keyword;
		};
		static_assert(sizeof(EntryPointData) == 0x10);

		static constexpr int TypeID = 40;
	public:
		~TESFurniture() override;

		// override (TESObjectACTI)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		bool        Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;
		bool        GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		bool        CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;
	public:
		BSTArray<EntryPointData>						entryPointDataArray;
		WorkBenchData									workBenchData;
		uint16_t										padE2;
		uint32_t										furnFlags;
		SpellItem*										associatedForm;
	};
	static_assert(sizeof(TESFurniture) == 0xE0);
}