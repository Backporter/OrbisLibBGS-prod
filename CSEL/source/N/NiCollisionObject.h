#pragma once

#include "../N/NiObject.h"

namespace ConsoleRE
{
	class NiAVObject;

	class NiCollisionObject : public NiObject
	{
	public:
		~NiCollisionObject() override = 0;

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
	public:
		NiAVObject* sceneObject;
	};
	static_assert(sizeof(NiCollisionObject) == 0x18);

}