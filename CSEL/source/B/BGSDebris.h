#pragma once

#include "../B/BGSPreloadable.h"
#include "../B/BSTArray.h"
#include "../B/BSTList.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct BGSDebrisData
	{
	public:
		enum class BGSDebrisDataFlags
		{
			kNone = 0,
			kCollisionData = 1 << 0
		};
	public:
		int8_t												percentage;
		uint8_t												flags;
		uint16_t											pad02;
		uint32_t											pad04;
		const char*											fileName;
		BSTArray<void*>										textureIDs;
		BSTArray<uint32_t>									addons;
	};
	static_assert(sizeof(BGSDebrisData) == 0x30);

	class BGSDebris : public TESForm, public BGSPreloadable
	{
	public:
		static constexpr int TypeID = 88;

		~BGSDebris() override;
	public:
		BSSimpleList<BGSDebrisData*> data;	
	};
	static_assert(sizeof(BGSDebris) == 0x38);
}