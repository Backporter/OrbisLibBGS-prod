#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IStackCallbackSaveInterface
		{
		public:
			virtual ~IStackCallbackSaveInterface();
			
			// add
			virtual void Unk_02() = 0;
			virtual void Unk_03() = 0;
		private:
		};
	}
}