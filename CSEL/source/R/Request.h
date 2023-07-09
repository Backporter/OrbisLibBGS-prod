#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	namespace bgs
	{
		namespace saveload
		{
			// 0x18
			class Request : public BSIntrusiveRefCounted
			{
			public:
				Request();
				virtual ~Request();
			public:
				uint32_t Unk0C;
				uint32_t Unk10;
				uint32_t Unk14;
			};
			static_assert(sizeof(Request) == 0x18, "");
		}
	}
}