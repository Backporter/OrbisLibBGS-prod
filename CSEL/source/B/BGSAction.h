#pragma once

#include "../B/BGSKeyword.h"

namespace ConsoleRE
{
	class BGSAction : public BGSKeyword
	{
	public:
		static constexpr int TypeID = 6;

		~BGSAction() override;
	public:
		uint32_t index;
	};
}