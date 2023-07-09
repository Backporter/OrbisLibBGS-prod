#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSTEvent.h"
#include "../B/BSBound.h"
#include "../N/NiRefObject.h"
#include "../H/hkVector4.h"
#include "../H/hkStepInfo.h"
#include "../H/hkTransform.h"
#include "../H/hkpCharacterContext.h"
#include "../H/hkpCharacterControl.h"
#include "../H/hkpCharacterState.h"

// hkpCharacterStateType

namespace ConsoleRE
{
	class bhkCharacterMoveFinishEvent;
	class bhkICharOrientationController;

	// 0x310?
	class bhkCharacterController : public NiRefObject, public BSTEventSource<bhkCharacterMoveFinishEvent>
	{
	public:
		~bhkCharacterController() override;

		// add
		virtual void  GetPositionImpl(hkVector4& a_pos, bool a_applyCenterOffset);
		virtual void  SetPositionImpl(const hkVector4& a_pos, bool a_applyCenterOffset, bool a_forceWarp);
		virtual void  GetTransformImpl(hkTransform& a_tranform);
		virtual void  SetTransformImpl(const hkTransform& a_tranform);
		virtual void  GetLinearVelocityImpl(hkVector4& a_velocity) const;
		virtual void  SetLinearVelocityImpl(const hkVector4& a_velocity);											 
		virtual void  Unk_02(void);          
		virtual void  Unk_03(void);          
		virtual void  Unk_04(void);          
		virtual void  Unk_05(void);          
		virtual void  Unk_06(void);          
		virtual void  Unk_07(void);		 
		virtual void  Unk_08(void);          
		virtual void  Unk_09(void);          
		virtual void  Unk_10(void);          
		virtual float Unk_11(void);		 
		virtual void  Unk_12(void);          
		virtual void  Unk_13(void);        
	public:
		hkVector4						forwardVec;
		hkStepInfo						stepInfo;
		hkVector4						outVelocity;
		hkVector4						initialVelocity;
		hkVector4						velocityMod;
		hkVector4						direction;
		hkVector4						rotCenter;
		hkVector4						pushDelta;
		hkVector4						fakeSupportStart;
		hkVector4						up;
		hkVector4						supportNorm;
		BSBound							collisionBound;
		BSBound							bumperCollisionBound;
		uint64_t						Unk170;
		uint64_t						Unk178;
		bhkICharOrientationController*	orientationCtrl;
		uint64_t						Unk188;
		hkpSurfaceInfo                  surfaceInfo;
		hkpCharacterContext             context;
		uint32_t						flags;
		hkpCharacterStateType			wantState;
		float                           velocityTime;
		float                           rotMod;
		float                           rotModTime;
		float                           calculatePitchTimer;
		float                           acrobatics;
		float                           center;
		float                           waterHeight;
		float                           jumpHeight;
		float                           fallStartHeight;
		float                           fallTime;
		float                           gravity;
		float                           pitchAngle;
		float                           rollAngle;
		float                           pitchMult;
		float                           scale;
		float                           swimFloatHeight;
		float                           actorHeight;
		float                           speedPct;
		uint32_t						pushCount;
		uint32_t						unk254;
		uint64_t						unk258;
		uint64_t						unk260;
		void*							shapes[2];
		uint64_t						unk278;
		uint64_t						unk280;
		uint64_t						unk288;
		uint64_t						unk290;
		void*							supportBody;
		float                           bumpedForce;
		uint32_t						pad2A4;
		void*							bumpedBody;
		void*							bumpedCharCollisionObject;
		BSTHashMap<UnkKey, UnkValue>    unk2B8;
		uint64_t						unk2D8;
		uint64_t						unk2E0;
		uint64_t						unk2E8;
		uint64_t						unk2F0;
	};
	static_assert(offsetof(bhkCharacterController, collisionBound)		 == 0x110);
	static_assert(offsetof(bhkCharacterController, bumperCollisionBound) == 0x140);
	static_assert(offsetof(bhkCharacterController, context)				 == 0x1D0);
	static_assert(offsetof(bhkCharacterController, fallStartHeight)		 == 0x228);
	static_assert(sizeof(bhkCharacterController) == 0x300);
}