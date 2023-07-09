#pragma once

#include "../../../OrbisUtil/include/Macro.h"
#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSAtomic.h"
#include "../T/TESCamera.h"

namespace ConsoleRE
{
	class bhkRigidBody;

	struct CameraStates
	{
		enum CameraState : uint32_t
		{
			kFirstPerson = 0,
			kAutoVanity,
			kVATS,
			kFree,
			kIronSights,
			kFurniture,
			kPCTransition,
			kTween,
			kAnimated,
			kThirdPerson,
			kMount,
			kBleedout,
			kDragon,

			kTotal
		};
	};
	using CameraState = CameraStates::CameraState;

	class PlayerCamera : public TESCamera
	{
	public:
		~PlayerCamera() override;

		// override (TESCamera)
		void SetCameraRoot(NiPointer<NiNode> a_root) override;

		static PlayerCamera* GetSingleton()
		{
			Relocation<PlayerCamera**> Singleton("", 0x30C9890);
			return *Singleton;
		}

		void UpdateThirdPerson(bool a_weaponDrawn)
		{
			using func_t = decltype(&PlayerCamera::UpdateThirdPerson);
			Relocation<func_t> func("", 0x9D0030);
			func(this, a_weaponDrawn);
		}
	public:
		uint32_t							cameraTarget;
		BSTSmallArray<TESCameraState*, 13>	tempReturnStates;
		BSTSmartPointer<TESCameraState>		cameraStates[13];
		void*								Unk118;
		NiPointer<bhkRigidBody>				rigidBody;
		uint32_t							objectFadeHandle;
		mutable BSSpinLock                  lock;
		float                               worldFOV;
		float                               firstPersonFOV;
		NiPoint3							pos;
		float								idleTimer;
		float								yaw;
		uint32_t							Unk15C;             
		uint32_t							Unk160;             
		bool                                allowAutoVanityMode;
		bool                                bowZoomedIn;
		bool                                isWeapSheathed;
		bool                                isProcessed;
	};
	static_assert(sizeof(PlayerCamera) == 0x168);
}