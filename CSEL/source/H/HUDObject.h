#pragma once

#include "../G/GFxValue.h"
#include "../G/GPtr.h"

#include "../F/FxDelegateArgs.h"
#include "../G/GFxMovieView.h"

namespace ConsoleRE
{
	class UIMessage;

	class HUDObject
	{
	public:
		struct HudComponents
		{
			enum HudComponent : uint32_t
			{
				kThis = 0,
				kHudElements,
				kQuestUpdateBaseInstance,
				kEnemyHealthMeter,
				kStealthMeterInstance,
				kSneakAnimInstance,
				kBracketsInstance,
				kRolloverNameInstance,
				kSneakTextHolder,
				kSneakTextInstance
			};
		};

		using HudComponent = HudComponents::HudComponent;
	public:
		HUDObject(GFxMovieView* a_view);
		virtual ~HUDObject();

		virtual void	 Update() = 0;
		virtual bool	 ProcessMessage(UIMessage* a_message);
		virtual void	 RegisterHUDComponent(FxDelegateArgs& a_params);
		virtual void	 CleanUp();
	public:
		GPtr<GFxMovieView>	 view;
		GFxValue			 root;
	};
	static_assert(sizeof(HUDObject) == 0x28);
}