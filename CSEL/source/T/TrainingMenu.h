#pragma once

#include "../B/BSTEvent.h"
#include "../G/GFxValue.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class MenuOpenCloseEvent;

	class TrainingMenu : public IMenu, public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		constexpr static inline const char* MENU_NAME = "Training Menu";

		~TrainingMenu() override;

		// override (IMenu)
		void				Accept(CallbackProcessor* a_cbReg) override;
		uint32_t			ProcessMessage(UIMessage& a_message) override;

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;
	public:
		void*			unk38;
		uint32_t		skill;
		uint32_t		unk44;
		GFxValue		trainingMenuObj;
		GFxValue		skillName;
		GFxValue		skillMeter;
		GFxValue		trainerSkill;
		GFxValue		timesTrained;
		GFxValue		trainCost;
		GFxValue		currentGold;
	};
	static_assert(sizeof(TrainingMenu) == 0xF0);
}