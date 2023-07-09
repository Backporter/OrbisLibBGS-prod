#pragma once

#include "../B/BSSoundHandle.h"
#include "../N/NiMatrix3.h"
#include "../N/NiSmartPointer.h"
#include "../T/ThirdPersonState.h"

namespace ConsoleRE
{
	class NiAVObject;

	class BleedoutCameraState : public ThirdPersonState
	{
	public:
		~BleedoutCameraState() override;

		 // override (ThirdPersonState)
		void Begin() override;
		void End() override;
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
	public:
		NiMatrix3             rotationMtx;
		float                 zoom;
		float                 pitch;
		float                 yaw;
		float                 randHeading;
		NiPointer<NiAVObject> animatedBone;
		BSSoundHandle         activeSound;
		bool                  useCurrentHeading;
		uint8_t				  pad135;
		uint16_t			  pad136;
	};
	static_assert(sizeof(BleedoutCameraState) == 0x130);
}