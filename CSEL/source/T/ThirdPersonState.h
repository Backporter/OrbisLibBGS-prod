#pragma once

#include "../B/BSFixedString.h"
#include "../N/NiPoint2.h"
#include "../N/NiPoint3.h"
#include "../N/NiQuaternion.h"
#include "../P/PlayerInputHandler.h"
#include "../T/TESCameraState.h"

namespace ConsoleRE
{
	class NiNode;
	class NiAVObject;

	class ThirdPersonState : public TESCameraState, public PlayerInputHandler
	{
	public:
		~ThirdPersonState() override;

		// override (TESCameraState)
		void Begin() override;
		void End() override;
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		void GetRotation(NiQuaternion& a_rotation) override;
		void GetTranslation(NiPoint3& a_translation) override;
		void SaveGame(void* a_buf) override;
		void LoadGame(void* a_buf) override;
		void Revert(void* a_buf) override;

		// PlayerInputHandler
		bool CanProcess(InputEvent* a_event) override;
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;
		
		// add
		virtual void SetCameraHandle(void* a_handle);
		virtual void Unk_0A(void);
		virtual void ProcessWeaponDrawnChange(bool a_drawn);
		virtual bool GetFreeRotationMode();
		virtual void SetFreeRotationMode(bool a_weaponSheathed);
		virtual void UpdateRotation();
		virtual void HandleLookInput(NiPoint2& a_input);
	public:
		NiAVObject*   thirdPersonCameraObj;
		NiNode*       thirdPersonFOVControl;
		NiPoint3      translation;
		NiQuaternion  rotation;
		NiPoint3      posOffsetExpected;
		NiPoint3      posOffsetActual;
		float         targetZoomOffset;
		float         currentZoomOffset;
		float         targetYaw;
		float         currentYaw;
		float         savedZoomOffset;
		float         pitchZoomOffset;
		float         unk8C;
		NiPoint3      collisionPos;
		float         collisionPosValid;
		uint64_t	  unkA0;
		BSFixedString animatedBoneName;
		NiQuaternion  animationRotation;
		uint64_t	  unkC0;
		uint64_t	  unkC8;
		uint32_t	  unkD0;
		NiPoint2      freeRotation;
		bool          freeRotationEnabled;
		bool          stateNotActive;
		uint16_t	  unkDC;
		bool          toggleAnimCam;
		bool          applyOffsets;
		uint16_t	  unkE2;
	};
	static_assert(sizeof(ThirdPersonState) == 0xE8);
}