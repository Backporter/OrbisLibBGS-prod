#pragma once

#include "../B/BSTArray.h"
#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	struct BottomBar;
	struct ItemCard;
	struct ItemList;

	class BarterMenu : public IMenu
	{
	public:
		constexpr static auto MENU_NAME = "BarterMenu";
	public:
		~BarterMenu() override;
		
		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;
		uint32_t		   ProcessMessage(UIMessage& a_message) override;
		void               PostDisplay() override;

		uint32_t GetTargetRefHandle()
		{
			Relocation<uint32_t*> ID("", 0x3198A6C);
			return *ID;
		}
	public:
		ItemList*       itemList;
		ItemCard*       itemCard;
		BottomBar*      bottomBar;
		GFxValue        root;
		uint64_t		unk60;
		uint64_t		unk68;
		uint64_t		unk70;
		uint8_t			unk78;
		uint8_t			pad79;
		uint16_t		pad7A;
		uint32_t		pad7C;
		BSTArray<void*> unk80;
		uint64_t		unk98;
		uint32_t		unkA0;
		bool			pcControlsReady;	
		uint8_t			padA5;
		uint16_t		padA6;
	};
	static_assert(sizeof(BarterMenu) == 0xA0);
}