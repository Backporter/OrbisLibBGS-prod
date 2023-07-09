#pragma once

#include "../G/GRefCountImplCore.h"

namespace ConsoleRE
{
	class GRefCountImpl : public GRefCountImplCore
	{
	public:
		~GRefCountImpl() override = default;

		// add
		void IncremntRef()
		{
			__sync_fetch_and_add(&Ref, 1);
		}

		void Release()  
		{  
			if (!__sync_sub_and_fetch(&Ref, 1))
			{
				delete this;
			}
		}
	};
	static_assert(sizeof(GRefCountImpl) == 0x10);
}