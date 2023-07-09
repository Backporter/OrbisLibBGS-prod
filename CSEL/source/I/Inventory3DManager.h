#pragma once
#include "../../../OrbisUtil/include//Relocation.h"

#include "../M/MenuEventHandler.h"
#include "../E/ExtraDataList.h"
#include "../I/Inventory3DItem.h"
#include "../B/BSTSmallArray.h"

namespace ConsoleRE
{
	class Inventory3DManager : public MenuEventHandler
	{
	public:
		// 0xA18920
		Inventory3DManager();
		virtual ~Inventory3DManager();

		static Inventory3DManager* GetSingleton()
		{
			Relocation<Inventory3DManager**> Singleton("Inventory3DManager:Singleton", 0x3148918);
			return *Singleton;
		}
	public:
		NiPoint3                                      Unk10;
		NiPoint3                                      Unk1C;
		float                                         Unk28;
		float                                         Unk2C;
		uint32_t									  Unk30;
		uint32_t									  Unk34;
		TESObjectREFR*								  Unk38;
		ExtraDataList								  Unk40;
		uint8_t										  Unk60[0x118];
		uint32_t									  Unk178;
		uint32_t									  zoomProgress;
	};
}