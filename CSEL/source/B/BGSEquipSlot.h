#pragma once

#include "../T/TESForm.h"
#include "../B/BSTArray.h"

#include <stdio.h>
#include <stdint.h>

namespace ConsoleRE
{
	class BGSEquipSlot : public TESForm
	{
	public:
		static constexpr int TypeID = 120;
		BGSEquipSlot();
		virtual ~BGSEquipSlot();
		virtual void Unk_02();
		virtual void Unk_03();
		virtual bool Unk_04();
		virtual void Unk_05();

	public:
		BSTArray<BGSEquipSlot*> Parent;
		uint32_t				Flag;
		uint32_t				PADDING;
	};
	static_assert(sizeof(BGSEquipSlot) == 0x38, "#");
}