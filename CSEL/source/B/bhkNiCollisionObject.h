#pragma once

#include "../N/NiCollisionObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class bhkWorldObject;

	class bhkNiCollisionObject : public NiCollisionObject
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kActive = 1 << 0,
			kNotify = 1 << 2,
			kSetLocal = 1 << 3,
			kDebugDisplay = 1 << 4,
			kUseVelocity = 1 << 5,
			kReset = 1 << 6,
			kSyncOnUpdate = 1 << 7,
			kAnimTargeted = 1 << 10,
			kDismemberLimb = 1 << 11
		};
	public:
		~bhkNiCollisionObject() override;

		// override (NiCollisionObject)
		const NiRTTI*         GetRTTI() const override;
		bhkNiCollisionObject* AsBhkNiCollisionObject() override;
		void                  LoadBinary(NiStream& a_stream) override;
		void                  LinkObject(NiStream& a_stream) override;
		bool                  RegisterStreamables(NiStream& a_stream) override;
		void                  SaveBinary(NiStream& a_stream) override;
		bool                  IsEqual(NiObject* a_object) override;
	public:
		uint32_t					flags;
		uint32_t					pad1C;
		NiPointer<bhkWorldObject>   body;
	};
	static_assert(sizeof(bhkNiCollisionObject) == 0x28);
}
