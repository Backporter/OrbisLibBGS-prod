#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class ModManagerMenu : 
		public IMenu, 
		public MenuEventHandler, 
		public GFxFunctionHandler
	{
	public:
		constexpr static inline const char* MENU_NAME = "Mod Manager Menu";
	public:
		~ModManagerMenu() override;

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;
		void     AdvanceMovie(float a_interval, uint32_t a_currentTime) override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;
	public:
		uint8_t  unk50;
		uint8_t  pad51;
		uint16_t pad52;
		uint32_t pad54;
	};
	static_assert(sizeof(ModManagerMenu) == 0x50);
}