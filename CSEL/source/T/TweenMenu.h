#pragma once

#include "../I/IMenu.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	// 0x48
	class TweenMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "TweenMenu";
		
		~TweenMenu() override;

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;
		uint32_t		   ProcessMessage(UIMessage& a_message) override;
		void               PostDisplay() override;
	public:
		BSTArray<void*> perkData;
		float			Unk40;
		float			Unk44;
	};
	static_assert(sizeof(TweenMenu) == 0x48);
}