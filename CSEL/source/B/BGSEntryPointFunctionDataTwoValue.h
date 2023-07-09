#pragma once
#include "../B/BGSEntryPointFunctionData.h"
namespace ConsoleRE
{
	class BGSEntryPointFunctionDataTwoValue : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataTwoValue();
		virtual ~BGSEntryPointFunctionDataTwoValue();
	public:
		float Unk08[2];
	};
}