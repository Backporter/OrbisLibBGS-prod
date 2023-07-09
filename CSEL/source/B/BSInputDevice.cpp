#include "../B/BSInputDevice.h"

namespace ConsoleRE
{
	BSInputDevice::BSInputDevice(uint32_t a_device) : 
		BSIInputDevice(), device(a_device), pad0C(0), deviceButtons { }, buttonNameIDMap { }
	{
	}

	BSInputDevice::~BSInputDevice()
	{}

	bool	 BSInputDevice::GetKeyMapping(uint32_t a_key, BSFixedString& a_mapping)
	{
		using func_t = decltype(&BSInputDevice::GetKeyMapping);
		Relocation<func_t, 0> func("", 0xE35A70);
		return func(this, a_key, a_mapping);
	}

	uint32_t BSInputDevice::GetMappingKey(BSFixedString a_mapping)
	{
		using func_t = decltype(&BSInputDevice::GetMappingKey);
		Relocation<func_t, 0> func("", 0xE35B20);
		return func(this, a_mapping);
	}

	bool	 BSInputDevice::GetInputButton(uint32_t a_key, InputButton*& a_inputButton)
	{
		using func_t = decltype(&BSInputDevice::GetInputButton);
		Relocation<func_t, 0> func("", 0xE35BB0);
		return func(this, a_key, a_inputButton);
	}
	
	bool	 BSInputDevice::IsEnabled(void)
	{
		return true;
	}

	bool	 BSInputDevice::IsKeyboard() const
	{
		return device == static_cast<uint32_t>(INPUT_DEVICE::kKeyboard);
	}

	bool	 BSInputDevice::IsMouse() const
	{
		return device == INPUT_DEVICE::kMouse;
	}

	bool	 BSInputDevice::IsGamepad() const
	{
		return device == INPUT_DEVICE::kGamepad;
	}

	bool	 BSInputDevice::IsPressed(uint32_t a_keyCode)
	{
		auto it = deviceButtons.findT(a_keyCode);
		return (it != nullptr) && ((*it)->heldDownSecs > 0.0);
	}

}