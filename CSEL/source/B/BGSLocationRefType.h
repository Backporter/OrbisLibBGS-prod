#pragma once

#include "../B/BGSKeyword.h"

namespace ConsoleRE
{
	class BGSLocationRefType : public BGSKeyword
	{
	public:
		static constexpr int TypeID = 5;
	public:
		~BGSLocationRefType() override;

		// override (BGSKeyword)
		void InitItemImpl() override;
	public:
	};
	static_assert(sizeof(BGSLocationRefType) == 0x28);
}