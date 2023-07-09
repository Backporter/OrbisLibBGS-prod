#pragma once

#include "../H/hkReferencedObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	class hkpCharacterContext;
	struct hkpCharacterInput;
	struct hkpCharacterOutput;

	struct hkpCharacterStateTypes
	{
		enum hkpCharacterStateType : uint32_t
		{
			kOnGround = 0,
			kJumping,
			kInAir,
			kClimbing,
			kFlying,
			kUserState0,
			kSwimming = kUserState0,
			kUserState1,
			kUserState2,
			kUserState3,
			kUserState4,
			kUserState5,

			kTotal
		};
	};

	using hkpCharacterStateType = hkpCharacterStateTypes::hkpCharacterStateType;

	class hkpCharacterState : public hkReferencedObject
	{
	public:
		~hkpCharacterState() override;

		// add
		virtual hkpCharacterStateType GetType() const = 0;
		virtual void                  EnterState(hkpCharacterContext& a_context, hkpCharacterStateType a_prevState, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output);
		virtual void                  LeaveState(hkpCharacterContext& a_context, hkpCharacterStateType a_nextState, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output);
		virtual void                  Update(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) = 0;
		virtual void                  Change(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) = 0;
	};
	static_assert(sizeof(hkpCharacterState) == 0x10);
}