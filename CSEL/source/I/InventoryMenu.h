#pragma once

#include "../B/BSTArray.h"
#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class GFxMovieView;
	class TESObjectREFR;
	struct BottomBar;
	struct ItemCard;
	struct ItemList;

	class InventoryMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "InventoryMenu";
	public:
		~InventoryMenu() override;

		// override (IMenu)
		void				Accept(CallbackProcessor* a_processor) override;
		uint32_t			ProcessMessage(UIMessage& a_message) override;
		void				PostDisplay() override;
	public:
		GFxValue        root;
		ItemList*       itemList;
		ItemCard*       itemCard;
		BottomBar*      bottomBar;
		BSTArray<void*> unk60;
		uint8_t			unk78;
		uint8_t			pad79;
		uint16_t		pad7A;
		uint32_t		unk7C;
		bool            pcControlsReady;
		uint8_t			unk81;
		uint16_t		pad82;
		uint32_t		pad84;
	};
	static_assert(sizeof(InventoryMenu) == 0x80);
}