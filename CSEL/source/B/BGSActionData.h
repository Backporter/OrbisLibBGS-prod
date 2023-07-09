#pragma once

#include "../A/ActionInput.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BGSActionData : public ActionInput
	{
	public:
		~BGSActionData() override;

		// add
		virtual BGSActionData* Clone() const;
		virtual bool           Process();
	public:
		BSFixedString	unk28;
		BSFixedString	unk30;
		uint64_t		unk38;
		uint64_t		unk40;
		uint64_t		unk48;
		uint64_t		unk50;
	};
	static_assert(sizeof(BGSActionData) == 0x58);
}