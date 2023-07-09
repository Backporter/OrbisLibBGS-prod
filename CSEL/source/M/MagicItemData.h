#pragma once

#include "../T/TESForm.h"
#include "../G/GFxValue.h"

namespace ConsoleRE
{
	class MagicItemData
	{
	public:
		virtual ~MagicItemData();
		
		// add
		virtual uint32_t Unk_02();
		virtual uint32_t Unk_03();
		virtual uint32_t Unk_04();
		virtual bool	 Unk_05();
		virtual bool	 Unk_06();
		virtual bool	 Unk_07();
	public:
		uint64_t	Unk8;
		uint16_t	Unk10;
		uint16_t	Unk12;
		TESForm*	Unk18;
		GFxValue	Unk20;
		uint8_t		Unk48[0x10];
	};
	static_assert(sizeof(MagicItemData) == 0x48);
}