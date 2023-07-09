#pragma once

#include "../I/IFunctionArguments.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class ZeroFunctionArguments : public IFunctionArguments
		{
		public:
			bool Unk_02(BSScrapArray<Variable>* a_dst) override;
		};
		static_assert(sizeof(ZeroFunctionArguments) == 0x8);
	}
}