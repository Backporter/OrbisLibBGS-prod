#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../N/NiPoint2.h"

namespace ConsoleRE
{
	class MenuScreenData
	{
	public:
		static MenuScreenData* GetSingleton()
		{
			Relocation<MenuScreenData**> Singleton("", 0x3148ED0);
			return *Singleton;
		}
	public:
		NiPoint2      mousePos;
		float         unk0C;
		float         unk10;
		float         screenWidth;
		float         screenHeight;
		float         mouseSensitivity;
		float         unk20;
		float         unk24;
		float         unk28;
		uint32_t	  unk2C;
	};
}