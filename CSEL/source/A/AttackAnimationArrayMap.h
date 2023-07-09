#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"
#include "../N/NiRefObject.h"

namespace ConsoleRE
{
	class AttackAnimationArrayMap : 
		public NiRefObject, 
		public BSTHashMap<uint32_t, BSTArray<UnkValue>*>
	{
	public:
		virtual ~AttackAnimationArrayMap();
	};
	static_assert(sizeof(AttackAnimationArrayMap) == 0x30);
}