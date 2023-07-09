#pragma once

#include "../G/GFxFunctionHandler.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class CreditsMenu :
		public IMenu,
		public GFxFunctionHandler
	{
	public:
		constexpr static const char* MENU_NAME = "Credits Menu";
	public:
		~CreditsMenu() override;

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;
	};
	static_assert(sizeof(CreditsMenu) == 0x40);
}