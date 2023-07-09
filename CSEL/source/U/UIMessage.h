#pragma once

#include "../B/BSFixedString.h"

#include <stdint.h>

namespace ConsoleRE
{
	class IUIMessageData;

	enum UI_MESSAGE_TYPE
	{
		kUpdate = 0,
		kShow = 1,
		kReshow = 2,
		kHide = 3,
		kForceHide = 4,

		kScaleformEvent = 6,   // BSUIScaleformData
		kUserEvent = 7,        // BSUIMessageData
		kInventoryUpdate = 8,  // InventoryUpdateData
		kUserProfileChange = 9,
		kMUStatusChange = 10,
		kResumeCaching = 11,
		kUpdateController = 12,
		kChatterEvent = 13
	};

	class UIMessage
	{
	public:
		BSFixedString                                    menu;      
		UI_MESSAGE_TYPE									 type;
		uint32_t										 pad0C;
		IUIMessageData*                                  data;      
		bool                                             isPooled;  
		uint8_t											 pad19;     
		uint16_t										 pad1A;     
		uint32_t										 pad1C;     
	};
	static_assert(sizeof(UIMessage) == 0x20, "#");
}