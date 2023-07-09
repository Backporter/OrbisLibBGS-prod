#pragma once
#include "../B/BGSEntryPointFunctionData.h"
#include "../B/BSFixedString.h"
namespace ConsoleRE
{
	class BGSEntryPointFunctionDataBooleanGraphVariable : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataBooleanGraphVariable();
		virtual ~BGSEntryPointFunctionDataBooleanGraphVariable();
	public:
		BSFixedString Unk08;
	};
}