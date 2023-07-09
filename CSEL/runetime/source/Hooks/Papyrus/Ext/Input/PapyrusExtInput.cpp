#include "../Input/PapyrusExtInput.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BSInputDeviceManager.h"
#include "../../../../../../source/I/InputEvent.h"
#include "../../../../../../source/C/ControlMap.h"

#if __ORBIS__ || __OPENORBIS__
#include "../../../../../../runetime/source/Hooks/Hooks_Orbis.h"
#endif

namespace PapyrusExtInput
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool IsButtonPressed(StaticFunctionTag*, uint32_t keycode)
	{
		return (Runetime::Hooks::_ScePadDataStorage.CurrentButton == keycode);
	}

	BSFixedString GetMappedControl(StaticFunctionTag* thisInput, int32_t keyCode)
	{
		if (keyCode < 0)
			return BSFixedString();

		ControlMap * inputManager = ControlMap::GetSingleton();
		if (!inputManager)
			return BSFixedString();

		BSFixedString inval;
		BSFixedString ret;

		ret = inputManager->GetUserEventName(keyCode, INPUT_DEVICE::kGamepad, ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
		if (ret == inval)
		{
			ret = inputManager->GetUserEventName(keyCode, INPUT_DEVICE::kMouse, ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
			if (ret == inval)
			{
				ret = inputManager->GetUserEventName(keyCode, INPUT_DEVICE::kKeyboard, ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
				if (ret == inval)
				{
					return inval;
				}
				else
				{
					return ret;
				}
			}
			else
			{
				return ret;
			}

		}
		else
		{
			return ret;
		}
	}

	int32_t GetMappedKey(StaticFunctionTag* thisInput, BSFixedString name, uint32_t deviceType)
	{
		ControlMap * inputManager = ControlMap::GetSingleton();
		if (!inputManager)
			return -1;

		uint32_t key = 0xFF;

		// Manual device selection
		if (deviceType != 0xFF)
		{
			key = inputManager->GetMappedKey(name, static_cast<INPUT_DEVICE>(deviceType), ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
		}
		// Auto-selected device
		else
		{
			// Gamepad
			BSInputDeviceManager *inputEventDispatcher = BSInputDeviceManager::GetSingleton();
			if (inputEventDispatcher && inputEventDispatcher->IsGamepadEnabled())
			{
				deviceType = INPUT_DEVICE::kGamepad;
				key = inputManager->GetMappedKey(name, INPUT_DEVICE::kGamepad, ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
			}
			// Mouse + Keyboard
			else
			{
				deviceType = INPUT_DEVICE::kKeyboard;
				key = inputManager->GetMappedKey(name, static_cast<INPUT_DEVICE>(deviceType), ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
				if (key == 0xFF)
				{
					deviceType = INPUT_DEVICE::kMouse;
					key = inputManager->GetMappedKey(name, static_cast<ConsoleRE::INPUT_DEVICE>(deviceType), ConsoleRE::UserEvents::INPUT_CONTEXT_ID::kGameplay);
				}
			}
		}

		if (key == 0xFF)
			return -1;

		return key;
	}

	bool RegisterInput(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsButtonPressed),  StaticFunctionTag, bool, uint32_t>                    ("IsKeyPressed",	   "Input", IsButtonPressed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMappedControl), StaticFunctionTag, BSFixedString, int32_t>            ("GetMappedControl", "Input", GetMappedControl));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMappedKey),     StaticFunctionTag, int32_t, BSFixedString, uint32_t>  ("GetMappedKey",     "Input", GetMappedKey));

		VM->SetCallableFromTasklets("Input", "IsKeyPressed",	  true);
		VM->SetCallableFromTasklets("Input", "GetMappedControl", true);
		VM->SetCallableFromTasklets("Input", "GetMappedKey",     true);

		return true;
	}
}