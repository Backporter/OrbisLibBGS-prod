#pragma once

#include "../B/BSTList.h"

namespace ConsoleRE
{
	class TESRegion;

	class TESRegionList : public BSSimpleList<TESRegion*>
	{
	public:
		virtual ~TESRegionList();
	private:
		bool	 ownsRegionMemory;
		uint8_t  Unk19;
		uint16_t Unk1A;
		uint32_t Unk1C;
	};
	static_assert(sizeof(TESRegionList) == 0x20);
}