#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class TutorialMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "Tutorial Menu";

		~TutorialMenu() override;

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;
		uint32_t		   ProcessMessage(UIMessage& a_message) override;
	public:
		GFxValue root;
	};
	static_assert(sizeof(TutorialMenu) == 0x48);
}