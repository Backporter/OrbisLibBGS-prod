#pragma once

#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	struct BottomBar;
	struct ItemCard;

	class MagicMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "MagicMenu";
	public:
		~MagicMenu() override;

		// override (IMenu)
		void     Accept(CallbackProcessor* a_processor) override;
		uint32_t ProcessMessage(UIMessage& a_message) override;
		void     PostDisplay() override;
	public:
		void*         unk30;
		ItemCard*     itemCard;
		BottomBar*    bottomBar;
		GFxValue      root;
		bool          pcControlsReady;
		uint8_t       pad61;
		uint16_t      pad62;
	};
	static_assert(sizeof(MagicMenu) == 0x68);
}