#pragma once

#include "../T/TESPackage.h"

namespace ConsoleRE
{
	class DialoguePackage : public TESPackage
	{
	public:
		static constexpr int TypeID = 79;
	public:
		~DialoguePackage() override;
	public:
		uint32_t   unk0E0;
		int32_t	   unk0E4;
		int32_t    unk0E8;
		int32_t    unk0EC;
		uint64_t   unk0F0;
		uint64_t   unk0F8;
	};
	static_assert(sizeof(DialoguePackage) == 0x100);
}