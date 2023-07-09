#pragma once

#include "../N/NiBinaryStream.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiMemStream : public NiBinaryStream
	{
	public:
		NiMemStream();
		virtual ~NiMemStream();												
		virtual int    NiMemStreamUnk_01(void);
		virtual void   NiMemStreamUnk_02(void);
		virtual void   NiMemStreamUnk_03(void);
		virtual void   NiMemStreamUnk_04(void);
		virtual void   NiMemStreamUnk_05(const void* dst, size_t length);
		virtual size_t NiMemStreamUnk_06(const void* src, size_t Length);
	private:
	};

}