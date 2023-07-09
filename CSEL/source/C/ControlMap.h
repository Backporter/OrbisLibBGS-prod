#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSInputDevice.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../I/InputDevices.h"
#include "../U/UserEvents.h"

#include <stdint.h>


namespace ConsoleRE
{
	class UserEventEnabled;

	class ControlMap : public BSTEventSource<UserEventEnabled>
	{
	public:
		using InputContextID = UserEvents::INPUT_CONTEXT_ID;
		using UEFlag = UserEvents::USER_EVENT_FLAG;

		enum : uint32_t
		{
			kInvalid = static_cast<uint8_t>(-1)
		};

		struct UserEventMapping
		{
		public:
			BSFixedString eventID;
			uint16_t	  inputKey;
			uint16_t	  modifier;
			uint8_t		  indexInContext;
			bool		  remappable;
			bool		  linked;
			uint32_t	  userEventGroupFlag;
		};
		static_assert(sizeof(UserEventMapping) == 0x18);

		struct InputContext
		{
		public:
			BSTArray<UserEventMapping> deviceMappings[INPUT_DEVICES::kTotal];
		};
		static_assert(sizeof(InputContext) == 0x40);

		struct LinkedMapping
		{
		public:
			BSFixedString  linkedMappingName;
			InputContextID linkedMappingContext;
			INPUT_DEVICE   device;
			InputContextID linkFromContext;
			uint32_t	   pad14;
			BSFixedString  linkFromName;
		};
		static_assert(sizeof(LinkedMapping) == 0x20);
	public:
		static ControlMap* GetSingleton()
		{
			Relocation<ControlMap**> Singleton("", 0x30CA060);
			return *Singleton;
		}
		
		int8_t			AllowTextInput(bool a_allow);
		uint32_t		GetMappedKey(const char* a_eventID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay);
		const char*		GetUserEventName(uint32_t ButtonID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay);

		bool			IsLookingControlsEnabled()  { return (enabledControls & static_cast<uint32_t>(UEFlag::kLooking)) == 1; }
		bool			IsMovementControlsEnabled() { return (enabledControls & static_cast<uint32_t>(UEFlag::kMovement)) == 1; }
	public:
		InputContext*				controlMap[InputContextID::kTotal];
		BSTArray<LinkedMapping>		linkedMappings;
		BSTArray<InputContextID>	contextPriorityStack;
		uint32_t					enabledControls;
		uint32_t					UnkF4;
		int8_t						textEntryCount;
		bool						ignoreKeyboardMouse;
		bool						ignoreActivateDisabledEvents;
		uint8_t						UnkFb;
		uint32_t					gamePadMapType;
	};
	static_assert(sizeof(ControlMap) == 0x100);
}