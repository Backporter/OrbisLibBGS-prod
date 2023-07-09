#pragma once

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class TESQuest;

	class BGSBaseAlias
	{
	public:
		static constexpr int TypeID = 139;
	public:
		virtual ~BGSBaseAlias();
	public:
		BSFixedString aliasName;
		TESQuest*     owningQuest;
		uint32_t	  aliasID;
		uint32_t      flags;
		uint16_t	  fillType;
	};
}