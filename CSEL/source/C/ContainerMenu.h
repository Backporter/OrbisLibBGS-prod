#pragma once

#include "../B/BSTArray.h"
#include "../I/IMenu.h"
#include "../U/UIMenuStrings.h"

namespace ConsoleRE
{
	struct ItemList;
	struct ItemCard;
	struct BottomBar;

	class ContainerMenu : public IMenu
	{
	public:
		virtual ~ContainerMenu();
		constexpr static inline const char* MENU_NAME = "ContainerMenu";
		
		enum class ContainerMode : uint32_t
		{
			kLoot = 0,
			kSteal = 1,
			kPickpocket = 2,
			kNPCMode = 3
		};

		uint32_t GetTargetRefHandle()
		{
			Relocation<uint32_t*> ID("gOpenedContainerObjectRefHandleId", 0x3199104);
			return *ID;
		}

		ContainerMode GetContainerMode()
		{
			return ContainerMode::kLoot;
		}
	public:
		GFxValue        root;
		ItemList*       itemList;
		ItemCard*       itemCard;
		BottomBar*      bottomBar;
		BSTArray<void*> Unk60;
		BSTArray<void*> Unk70;
		uint64_t		Unk80;
		uint8_t			Unk88;
		uint8_t			Unk89;
		uint16_t		Unk8A;
		uint32_t		Unk8C;
		uint64_t		Unk90;
		uint64_t		Unk98;
		uint32_t		value; // UnkA0;
		uint32_t		UnkA4;
		uint8_t			UnkA8;
		bool			bPCControlsReady;
	};
	static_assert(offsetof(ContainerMenu, Unk60) == 0x60, "ContainerMenu");
	static_assert(offsetof(ContainerMenu, Unk70) == 0x70, "ContainerMenu");
	static_assert(offsetof(ContainerMenu, value) == 0xA0, "ContainerMenu");
	static_assert(offsetof(ContainerMenu, bPCControlsReady) == 0xA9, "ContainerMenu");
}