#pragma once
#include "../B/BGSEntryPointFunctionData.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionDataOneValue : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataOneValue();
		virtual ~BGSEntryPointFunctionDataOneValue();
	public:
		float Unk08;
	};
}