#pragma once

#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class MenuOpenHandler : public MenuEventHandler
	{
	public:
		~MenuOpenHandler() override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessKinect(KinectEvent* a_event) override;
		bool ProcessButton(ButtonEvent* a_event) override;
	public:
	};
	static_assert(sizeof(MenuOpenHandler) == 0x10);
}