#pragma once

#include "../G/GFxValue.h"
#include "../H/HUDObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	class StealthMeter : public HUDObject
	{
	public:
		~StealthMeter() override;

		// override (HUDObject)
		void Update() override;
		bool ProcessMessage(UIMessage* a_message) override;
		void RegisterHUDComponent(FxDelegateArgs& a_params) override;
	public:
		GFxValue      stealthMeter;
		GFxValue      sneakAnim;
		GFxValue      sneakTextHolder;
		GFxValue      sneakText;
	};
}