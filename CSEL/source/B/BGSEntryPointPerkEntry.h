#pragma once

#include "../B/BGSPerkEntry.h"
#include "../F/FormTypes.h"
#include "../M/MemoryManager.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionData;
	class TESCondition;

	class BGSEntryPointPerkEntry : public BGSPerkEntry
	{
	public:
		struct EntryData  // DATA
		{
		public:
			enum class Function
			{
				kSetValue = 1,
				kAddValue = 2,
				kMultiplyValue = 3,
				kAddRangeToValue = 4,
				kAddActorValueMult = 5,
				kAbsoluteValue = 6,
				kNegativeAbsoluteValue = 7,
				kAddLeveledList = 8,
				kAddActivateChoice = 9,
				kSelectSpell = 10,
				kSelectText = 11,
				kSetToActorValueMult = 12,
				kMultiplyActorValueMult = 13,
				kMultiply1PlusActorValueMult = 14,
				kSetText = 15
			};
		public:
			uint8_t  entryPoint;
			uint8_t  function;
			uint8_t  numArgs;
			uint8_t  unk3;
		};
		static_assert(sizeof(EntryData) == 0x4);
	public:
		virtual ~BGSEntryPointPerkEntry();
	public:
		EntryData                  entryData;
		BGSEntryPointFunctionData* functionData;
		void*					   conditions;
		BGSPerk*                   perk;
	};
	static_assert(offsetof(BGSEntryPointPerkEntry, functionData) == 0x10);
	static_assert(sizeof(BGSEntryPointPerkEntry) == 0x28);
}