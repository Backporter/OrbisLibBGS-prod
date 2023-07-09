#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../B/BSTArray.h"
#include "../G/GFxValue.h"
#include "../H/HUDObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESQuest;
	class TESWordOfPower;

	class HUDNotifications : public HUDObject
	{
	public:
		struct Notification
		{
		public:
			BSString                text;
			BSString                status;
			BSFixedString           sound;
			BSTArray<BSFixedString> objectives;
			uint32_t				type{ 0 };
			uint32_t				pad44{ 0 };
			TESQuest*               quest{ nullptr };
			TESWordOfPower*         word{ nullptr };
			uint32_t				time{ 0 };
			uint32_t				pad5C{ 0 };
		};
		static_assert(sizeof(Notification) == 0x60);
	public:
		~HUDNotifications() override;

		// override (HUDObject)
		void Update() override;
		bool ProcessMessage(UIMessage* a_message) override;
		void RegisterHUDComponent(FxDelegateArgs& a_params) override;
		void CleanUp() override;
	public:
		BSTArray<Notification> queue;
		GFxValue               root;
		GFxValue               objectives;
		uint32_t			   time;
		float                  levelPoints;
	};
	static_assert(sizeof(HUDNotifications) == 0x70);
}