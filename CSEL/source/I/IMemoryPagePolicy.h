#pragma once

#include "../B/BSTSmartPointer.h"
#include "../M/MemoryPage.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		struct IMemoryPagePolicy
		{
		public:
			virtual ~IMemoryPagePolicy();

			// add (IMemoryPagePolicy)
			virtual uint32_t Unk_02() = 0;
			virtual uint32_t Unk_03(uint32_t, uint32_t, BSTAutoPointer<MemoryPage>&) = 0;
			virtual uint32_t Unk_04(BSTAutoPointer<MemoryPage>&) = 0;
			virtual void	 Unk_05(BSTAutoPointer<MemoryPage>&) = 0;
		private:
		};
	}
}