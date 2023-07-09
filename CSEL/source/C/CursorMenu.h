#pragma once

#include "../I/IMenu.h"
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class CursorMenu :
		public IMenu,
		public MenuEventHandler
	{
	public:
		constexpr static const char* MENU_NAME = "Cursor Menu";

	public:
		~CursorMenu() override;

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;
	};
	static_assert(sizeof(CursorMenu) == 0x40);
}