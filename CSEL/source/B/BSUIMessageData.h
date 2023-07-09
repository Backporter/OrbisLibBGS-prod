#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../I/IUIMessageData.h"

namespace ConsoleRE
{
	class BSUIMessageData : public IUIMessageData
	{
	public:
		union Data
		{
			bool			b;
			uint32_t		u;
			float			f;
			void*			p;
		};
		static_assert(sizeof(Data) == 0x8);
	public:
		~BSUIMessageData() override;
	public:
		BSString*     str;
		BSFixedString fixedStr;
		Data          data;
	};
}