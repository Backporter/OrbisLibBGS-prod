#pragma once
#include "../B/BGSEntryPointFunctionData.h"
#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionDataText : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataText();
		virtual ~BGSEntryPointFunctionDataText();
	public:
		BSFixedString Unk08;
	};
}