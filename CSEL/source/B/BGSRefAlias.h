#pragma once
#include "../B/BGSBaseAlias.h"

namespace ConsoleRE
{
	// 0x48
	class BGSRefAlias : public BGSBaseAlias
	{
	public:
		static constexpr int TypeID = 140;
	public:
		virtual ~BGSRefAlias();
	public:
		uint8_t DATA[8 * 3];
		void* conditions;
	};
	static_assert(sizeof(BGSRefAlias) == 0x48, "sizeof(BGSRefAlias) != 0x48");
}