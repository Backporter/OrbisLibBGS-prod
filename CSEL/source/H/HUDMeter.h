#pragma once

#include "../B/BSFixedString.h"
#include "../H/HUDObject.h"

namespace ConsoleRE
{
	class HUDMeter : public HUDObject
	{
	public:
		HUDMeter(GFxMovieView* a_view);
		~HUDMeter() override = default;

		// override (HUDObject)
		void Update() override;
		bool ProcessMessage(UIMessage* a_message) override;

		// add
		virtual float GetFillPct();

		void SetFillPct(bool a_forceUpdate);
	public:
		BSFixedString setPctName;
		BSFixedString setBlinkingName;
		BSFixedString fadeOutName;
		float         fillPct;
		uint32_t	  pad44;
	};
	static_assert(sizeof(HUDMeter) == 0x48);
}