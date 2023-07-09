#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class bhkWorld;

	class BSIRagdollDriver
	{
	public:
		virtual ~BSIRagdollDriver();

		virtual bool HasRagdoll()				               = 0;
		virtual bool AddRagdollToWorld()		               = 0;
		virtual bool RemoveRagdollFromWorld()                  = 0;
		virtual void SetWorld(bhkWorld* a_world)               = 0;
		virtual void ResetRagdoll(void)                        = 0;
		virtual void Unk_06(void)                              = 0;
		virtual void SetRagdollConstraintsFromBhkConstraints() = 0;
		virtual void SetMotionType(uint32_t a_motionType)	   = 0;
		virtual void Unk_09(void)                              = 0;
		virtual void ToggleSyncOnUpdate(bool a_disable)        = 0;
		virtual void Unk_0B(void)                              = 0;
		virtual void ToggleConstraints(bool a_disable)         = 0;
		virtual void Unk_0D(void)                              = 0;
	};
}