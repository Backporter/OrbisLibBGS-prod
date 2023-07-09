#pragma once

#include "../B/bhkNiCollisionObject.h"

namespace ConsoleRE
{
	class bhkCollisionObject : public bhkNiCollisionObject
	{
	public:
		~bhkCollisionObject() override;

		// override (bhkNiCollisionObject)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
	};
	static_assert(sizeof(bhkCollisionObject) == 0x28);
}
