#pragma once

#include "../B/BSTArray.h"
#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	struct ItemCard;
	struct ItemList;

	class GiftMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "GiftMenu";
	public:
		~GiftMenu() override;
		
		// override (IMenu)
		void				Accept(CallbackProcessor* a_processor) override;
		uint32_t			ProcessMessage(UIMessage& a_message) override;
		void				PostDisplay() override;

		static uint32_t GetTargetRefHandle();
	public:
		GFxValue        root;
		ItemList*       itemList;
		ItemCard*       itemCard;
		BSTArray<void*> unk58;
		uint64_t		unk60;
		bool            pcControlsReady;
	};
	static_assert(sizeof(GiftMenu) == 0x78);
}