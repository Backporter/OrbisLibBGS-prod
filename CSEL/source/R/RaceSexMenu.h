#pragma once

#include "../I/IMenu.h"
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class RaceSexMenu : public IMenu, public MenuEventHandler
	{
	public:
		constexpr static const char* MENU_NAME = "RaceSex Menu";
	public:
		virtual ~RaceSexMenu();
		
		// override (IMenu)
		void Accept(FxDelegateHandler::CallbackProcessor*) override;
		void Unk_03(void) override;
		uint32_t ProcessMessage(UIMessage& Unk0) override;
		void AdvanceMovie(float f1, uint32_t int1) override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent*) override;
		bool ProcessThumbstick(ThumbstickEvent*) override;
		bool ProcessMouseMove(MouseMoveEvent*) override;
		bool ProcessButton(ButtonEvent*) override;
	public:
		BSTArray<void*> Unk40[7];
	};
}