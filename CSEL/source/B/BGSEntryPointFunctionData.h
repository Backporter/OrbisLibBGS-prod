#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionData();
		virtual ~BGSEntryPointFunctionData();
		virtual uint32_t Unk_02(void*) = 0;
		virtual bool	 Unk_03(void*) = 0;
		virtual void	 Unk_04(void*);
		virtual void	 Unk_05(void*);
		virtual uint32_t Unk_06(void*);
		virtual void	 Unk_07(void*);
		virtual uint32_t Unk_08(void*);
	public:
	};
}