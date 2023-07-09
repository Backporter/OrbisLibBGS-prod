#include "../Camera/PapyrusExtCamera.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/P/PlayerCamera.h"
#include "../../../../../../source/P/PlayerCharacter.h"

namespace PapyrusExtCamera
{
	// I really hate doing this...
	using namespace ConsoleRE;

	int32_t GetCameraState(StaticFunctionTag * base)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera) 
		{
			for (int i = 0; i < 13; i++) 
			{
				if (playerCamera->currentState == playerCamera->cameraStates[i])
					return i;
			}
		}

		return -1;
	}

	void UpdateThirdPerson(StaticFunctionTag * base)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		PlayerCamera * camera = PlayerCamera::GetSingleton();
		if (pPC && camera) 
		{
			camera->UpdateThirdPerson(static_cast<ActorState*>(pPC)->IsWeaponDrawn());
		}
	}
	
	float GetWorldFieldOfView(StaticFunctionTag * base)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera) 
		{
			return playerCamera->worldFOV;
		}
	
		return 0;
	}
	
	void SetWorldFieldOfView(StaticFunctionTag * base, float fov)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera) 
		{
			playerCamera->worldFOV = fov;
		}
	}
	
	float GetFirstPersonFieldOfView(StaticFunctionTag * base)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera) 
		{
			return playerCamera->firstPersonFOV;
		}
	
		return 0;
	}
	
	void SetFirstPersonFieldOfView(StaticFunctionTag * base, float fov)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera) 
		{
			playerCamera->firstPersonFOV = fov;
		}
	}

	bool RegisterCamera(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCameraState),	         StaticFunctionTag, int32_t>     ("GetCameraState",			   "Camera", GetCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UpdateThirdPerson),         StaticFunctionTag, void>        ("UpdateThirdPerson",         "Camera", UpdateThirdPerson));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWorldFieldOfView),       StaticFunctionTag, float>       ("GetWorldFieldOfView",       "Camera", GetWorldFieldOfView));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetWorldFieldOfView),       StaticFunctionTag, void, float> ("SetWorldFieldOfView",       "Camera", SetWorldFieldOfView));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFirstPersonFieldOfView), StaticFunctionTag, float>       ("GetFirstPersonFieldOfView", "Camera", GetFirstPersonFieldOfView));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFirstPersonFieldOfView), StaticFunctionTag, void, float> ("SetFirstPersonFieldOfView", "Camera", SetFirstPersonFieldOfView));

		VM->SetCallableFromTasklets("Camera", "GetCameraState", true);

		return true;
	}
}