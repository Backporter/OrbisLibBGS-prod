#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class TESFaction;

	namespace PackageNS
	{
		struct CRIME_TYPES
		{
			enum CRIME_TYPE : uint32_t
			{
				kNone = static_cast<uint32_t>(-1),
				kSteal = 0,
				kPickpocket = 1,
				kTrespass = 2,
				kAttack = 3,
				kMurder = 4,
				kEscape = 5,
				kUnused = 6,

				kTotal = 7
			};
		};
		using CRIME_TYPE = CRIME_TYPES::CRIME_TYPE;
	}

	struct Crime
	{
	public:
		uint64_t				unk00;
		uint64_t				unk08;
		uint64_t				unk10;
		uint64_t				unk18;
		uint64_t				unk20;
		BSTArray<uint32_t>      actorsKnowOfCrime;
		uint64_t				unk40;
		uint64_t				unk48;
		uint64_t				unk50;
		uint64_t				unk58;
		TESFaction*             crimeFaction;
		uint32_t				unk68;
		mutable BSReadWriteLock lock;
		uint32_t				unk74;
	};
	static_assert(sizeof(Crime) == 0x80);
}