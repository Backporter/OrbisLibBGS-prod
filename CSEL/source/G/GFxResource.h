#pragma once

#include "../G/GNewOverrideBase.h"
#include <stdint.h>

namespace ConsoleRE
{
	class GFxResource : public GNewOverrideBase<2>
	{
	public:
		GFxResource();
		virtual ~GFxResource();

		// add
		virtual void		GetKey();
		virtual uint32_t	GetResourceTypeCode();
		virtual void*		GetResourceReport();
	public:
		volatile int32_t	m_refcount;
		int32_t				m_pad0C;
		void*				m_lib;
	};
}