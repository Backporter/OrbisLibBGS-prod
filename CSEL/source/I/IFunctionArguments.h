#pragma once

#include "../B/BSTArray.h"
#include "../V/Variable.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IFunctionArguments
		{
		public:
			IFunctionArguments() = default;
			virtual ~IFunctionArguments() = default;

			// add
			virtual bool Unk_02(BSScrapArray<Variable>* a_dst) = 0;
		public:
		};
		static_assert(sizeof(IFunctionArguments) == 0x8);
	}
}
