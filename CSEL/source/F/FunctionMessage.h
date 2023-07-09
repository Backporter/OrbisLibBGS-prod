#pragma once

#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			class Stack;
			class IFuncCallQuery;

			class FunctionMessage
			{
			public:
				~FunctionMessage();
			public:
				uint32_t                        type;     
				uint32_t						pad04;    
				BSTSmartPointer<Stack>          stack;    
				BSTSmartPointer<IFuncCallQuery> funcQuery;
			};
			static_assert(sizeof(FunctionMessage) == 0x18);
		}
	}
}