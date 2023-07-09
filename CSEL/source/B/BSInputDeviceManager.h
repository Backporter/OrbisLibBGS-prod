#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSTEvent.h"
#include "../I/InputDevices.h"

//
#include "../B/BSOrbisGamepadDevice.h"
#include "../B/BSOrbisKeyboardDevice.h"
#include "../B/BSOrbisVirtualKeyboardDevice.h"

namespace ConsoleRE
{
	class BSIInputDevice;
	class InputEvent;
	class BSRemoteGamepadEvent;

	class BSInputDeviceManager : public BSTEventSource<InputEvent*>
	{
	public:
		// 0xE36A90
		BSInputDeviceManager();
		~BSInputDeviceManager();

		static BSInputDeviceManager* GetSingleton()
		{
			Relocation<BSInputDeviceManager**> Singleton("", 0x313B280);
			return *Singleton;
		}

		//
		BSOrbisGamepadDevice*			GetGamepad()
		{
			return static_cast<BSOrbisGamepadDevice*>(devices[INPUT_DEVICE::kGamepad]);
		}

		BSOrbisKeyboardDevice*			GetKeyboard()
		{
			return static_cast<BSOrbisKeyboardDevice*>(devices[INPUT_DEVICE::kKeyboard]);

		}

		BSOrbisVirtualKeyboardDevice*	GetVirtualKeyboard()
		{
			return static_cast<BSOrbisVirtualKeyboardDevice*>(devices[INPUT_DEVICE::kVirtualKeyboard]);

		}

		bool							IsGamepadConnected()
		{
			return static_cast<bool>(GetGamepad());
		}

		bool							IsGamepadEnabled() 
		{ 
			auto gamepad = GetGamepad();
			return gamepad && gamepad->IsEnabled();
		}
		//
	public:
		BSIInputDevice*								devices[INPUT_DEVICES::kTotal];
		bool										queuedGamepadEnableValue;
		bool										valueQueued;
		bool										pollingEnabled;
		uint8_t										unk6B;
		uint32_t									Unk6C;
		BSTEventSource<BSRemoteGamepadEvent>		remoteGamepadEventSource;
	};
}