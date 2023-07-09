#pragma once

#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class Stack;

		namespace Internal
		{
			class IFuncCallQuery;

			class SuspendedStack
			{
			public:
				BSTSmartPointer<Stack>          stack;
				BSTSmartPointer<IFuncCallQuery> funcCallQuery;
			};
			static_assert(sizeof(SuspendedStack) == 0x10);
		}
	}
}