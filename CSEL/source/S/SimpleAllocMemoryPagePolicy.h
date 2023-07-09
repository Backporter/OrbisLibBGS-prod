#pragma once

#include "../B/BSAtomic.h"
#include "../I/IMemoryPagePolicy.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class SimpleAllocMemoryPagePolicy : public IMemoryPagePolicy
		{
		public:
			~SimpleAllocMemoryPagePolicy() override;

			// override (IMemoryPagePolicy)
			uint32_t Unk_02() override;
			uint32_t Unk_03(uint32_t, uint32_t, BSTAutoPointer<MemoryPage>&) override;
			uint32_t Unk_04(BSTAutoPointer<MemoryPage>&) override;
			void	 Unk_05(BSTAutoPointer<MemoryPage>&) override;
		public:
			uint32_t		Unk08;
			uint32_t		Unk0C;
			uint32_t		Unk10;
			uint32_t		Unk14;
			BSSpinLock		Unk18;
			uint32_t		Unk28;
			uint32_t		Unk2C;
		};
		static_assert(sizeof(SimpleAllocMemoryPagePolicy) == 0x30, "#");
	}
}