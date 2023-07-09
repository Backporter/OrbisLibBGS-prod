#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVirtualMachine;
		class StackFrame;

		class ISavePatcherInterface
		{
		public:
			virtual ~ISavePatcherInterface();

			// add
			virtual void PatchStackFrame(StackFrame* a_stackFrame, IVirtualMachine* a_vm) = 0;
		public:
		};
		static_assert(sizeof(ISavePatcherInterface) == 0x8);
	};
}