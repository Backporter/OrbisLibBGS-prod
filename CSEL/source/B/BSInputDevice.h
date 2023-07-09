#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIInputDevice.h"
#include "../B/BSTHashMap.h"
#include "../I/InputDevices.h"

namespace ConsoleRE
{
	class InputButton;

	class BSInputDevice : public BSIInputDevice
	{
	public:
		BSInputDevice(uint32_t a_device);
		~BSInputDevice() override;

		// override (BSIInputDevice)
		bool	 GetKeyMapping(uint32_t, BSFixedString&) override;
		uint32_t GetMappingKey(BSFixedString) override;
		bool	 GetInputButton(uint32_t, InputButton*&) override;
		bool	 IsEnabled(void) override;

		bool	 IsKeyboard() const;
		bool	 IsMouse() const;
		bool	 IsGamepad() const;
		bool	 IsPressed(uint32_t a_keyCode);
	public:
		uint32_t							device;
		uint32_t							pad0C;
		BSTHashMap<uint32_t, InputButton*>  deviceButtons;
		BSTHashMap<BSFixedString, uint32_t> buttonNameIDMap;
	};
	static_assert(offsetof(BSInputDevice, deviceButtons) == 0x10);
	static_assert(offsetof(BSInputDevice, buttonNameIDMap) == 0x30);
}