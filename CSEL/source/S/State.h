#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

namespace ConsoleRE
{
	namespace BSGraphics
	{
		class State
		{
		public:
			static State* GetSingleton()
			{
				Relocation<State*> Singleton("BSGraphics:State", 0x37DB2B0);
				return Singleton.get();
			}
		public:
			uint64_t        unk00;
			uint64_t        unk08;
			uint64_t        unk10;
			uint64_t        unk18;
			uint32_t        unk20;
			uint32_t        screenWidth;
			uint32_t        screenHeight;
			uint32_t        frameBufferViewport[2];
		};
	}
}