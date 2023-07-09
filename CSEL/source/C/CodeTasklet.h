#pragma once

#include "../I/IFuncCallQuery.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class ErrorLogger;
		class Stack;
		class StackFrame;

		namespace Internal
		{
			class VirtualMachine;

			class CodeTasklet : public IFuncCallQuery
			{
			public:
				virtual ~CodeTasklet();

				// override (IFuncCallQuery)
				bool Unk_02(uint32_t&, BSTSmartPointer<ObjectTypeInfo>&, BSFixedString&, Variable&, BSScrapArray<Variable>&) override;
			public:
				Stack*                                        stack;
				VirtualMachine*                               vm;
				ErrorLogger*                                  errorLogger;
				uint32_t									  resumeReason;
				uint32_t									  pad2C;
				StackFrame*                                   topFrame;
				uint32_t									  frameMemoryPage;
				int8_t										  jumpBitCount;
				int8_t										  localVarBitCount;
				int8_t										  memberVarBitCount;
				uint8_t										  pad3F;
				uint32_t									  instructionDataBitCount;
				uint32_t									  pad44;
				const void*                                   instructionDataStart;
			};
		}
	}
}