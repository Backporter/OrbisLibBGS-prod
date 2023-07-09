#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTTuple.h"
#include "../M/MemoryManager.h"
#include "../T/TypeInfo.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			struct NativeFunctionParameterInfo
			{
			public:
#if true
				explicit inline NativeFunctionParameterInfo(uint16_t a_numParams, uint16_t a_numLocals) : m_entries(a_numParams + a_numLocals), m_paramCount(a_numParams), m_totalEntries(a_numParams + a_numLocals)
				{}
#else
				NativeFunctionParameterInfo(uint16_t a_numParams, uint16_t a_numLocals)
				{
					using func_t = void(NativeFunctionParameterInfo* const, uint16_t, uint16_t);
					Relocation<func_t*> func("", 0x157B220);
					func(this, a_numParams, a_numLocals);
				}
#endif
			public:
				SimpleArray<BSTTuple<BSFixedString, TypeInfo>>	m_entries;
				uint16_t										m_paramCount;
				uint16_t										m_totalEntries;
			};
			static_assert(sizeof(NativeFunctionParameterInfo) == 0x10);
		}
	}
}