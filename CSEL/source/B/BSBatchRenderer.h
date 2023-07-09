#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"

namespace ConsoleRE
{
	class BSBatchRenderer
	{
	public:
		virtual ~BSBatchRenderer();
	public:
		BSTArray<void*>              unk008;
		BSTHashMap<UnkKey, UnkValue> unk018;
		uint64_t					 unk038;
		uint64_t					 unk040;
		uint64_t					 unk048;
		uint64_t					 unk050;
		void*                        unk058[16];
		uint64_t					 unk0D8;
		uint64_t					 unk0E0;
		uint64_t					 unk0E8;
		uint64_t					 Unk0F0;
		uint64_t					 Unk0F8;	
	};
	static_assert(sizeof(BSBatchRenderer) == 0x100);
}