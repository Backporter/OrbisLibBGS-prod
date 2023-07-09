#pragma once

#include "TESObjectMISC.h"

namespace ConsoleRE
{
	// 0xE0
	class TESSoulGem : public TESObjectMISC
	{
	public:
		static constexpr int TypeID = 52;
		
		~TESSoulGem() override;

		// override (TESObjectMISC)
		void InitializeData() override;
		void LoadImpl(TESFile* a_mod, uint32_t a_chunkID) override;
		void InitImpl() override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;

		//
		constexpr uint8_t GetContainedSoul() const noexcept { return currentSoul; }
		constexpr uint8_t GetMaximumCapacity() const noexcept { return soulCapacity; }
	public:
		TESSoulGem* linkedSoulGem;
		uint8_t		currentSoul;
		uint8_t		soulCapacity;
	};
	static_assert(sizeof(TESSoulGem) == 0xE0);
}