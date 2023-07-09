#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSTHashMap.h"

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class FragmentSystem
		{
		public:
			BSTHashMap<UnkKey, UnkValue> unk000;
			mutable BSSpinLock           unk020;
			BSTHashMap<UnkKey, UnkValue> unk030;
			mutable BSSpinLock           unk050;
			BSTHashMap<UnkKey, UnkValue> unk060;
			mutable BSSpinLock           unk080;
			BSTHashMap<UnkKey, UnkValue> unk090;
			mutable BSSpinLock           unk0B0;
			BSTHashMap<UnkKey, UnkValue> unk0C0;
			mutable BSSpinLock           unk0E0;
		};
		static_assert(sizeof(FragmentSystem) == 0xF0);
	}
}
