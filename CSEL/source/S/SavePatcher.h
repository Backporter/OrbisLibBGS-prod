#pragma once

#include "../I/ISavePatcherInterface.h"

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class SavePatcher : public BSScript::ISavePatcherInterface
		{
		public:
			~SavePatcher() override;

			// override (BSScript::ISavePatcherInterface)
			void PatchStackFrame(BSScript::StackFrame* a_stackFrame, BSScript::IVirtualMachine* a_vm) override;
		public:
		};
	}
}