#pragma once

#include "../B/BSTSmartPointer.h"
#include "../N/NiNode.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class TESCameraState;

	class TESCamera
	{
	public:
		virtual ~TESCamera();

		// add
		virtual void SetCameraRoot(NiPointer<NiNode> a_root);
		virtual void Update();

		void SetState(TESCameraState* a_state);
		void SetState_Impl(TESCameraState* a_rhs);
	public:
		float							rotationInput[2];
		float							translationInput[3];
		float							zoomInput;
		NiPointer<NiNode>				cameraRoot;
		BSTSmartPointer<TESCameraState>	currentState;
		bool							enabled;
		int8_t							Unk31;
		uint16_t						Unk32;
	};
	static_assert(sizeof(TESCamera) == 0x38);
}