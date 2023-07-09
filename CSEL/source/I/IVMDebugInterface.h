#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVMDebugInterface
		{
		public:
			virtual ~IVMDebugInterface();
			
			// add (IVMDebugInterface)
			virtual void Unk_02() = 0;
		private:
		};
	}
}