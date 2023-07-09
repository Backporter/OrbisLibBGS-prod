#pragma once

#include "../B/BSTArray.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSOutfit : public TESForm
	{
	public:
		static constexpr int TypeID = 124;
	public:
		~BGSOutfit() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BSTArray<TESForm*> outfitItems;
	};
	static_assert(sizeof(BGSOutfit) == 0x30);
}