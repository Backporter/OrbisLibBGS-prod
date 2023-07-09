#pragma once

#include "../B/BSTEvent.h"
#include "../G/GFxFunctionHandler.h"
#include "../I/IMenu.h"
#include "../I/ImageData.h"
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class MenuOpenCloseEvent;

	class CreationClubMenu :
		public IMenu,
		public MenuEventHandler,
		public GFxFunctionHandler,
		public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		constexpr static const char* MENU_NAME = "Creation Club Menu";
	public:
		~CreationClubMenu() override;

		// override (IMenu)
		void AdvanceMovie(float a_interval, uint32_t a_currentTime) override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;
	public:
		ImageData background;
		ImageData details;
	};
	static_assert(sizeof(CreationClubMenu) == 0x88);
}