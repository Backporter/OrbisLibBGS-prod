#pragma once

#include "../B/bhkSerializable.h"

namespace ConsoleRE
{
	class bhkWorldObject : public bhkSerializable
	{
	public:
		~bhkWorldObject() override;

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
	public:
		hkpWorld* world;
	};
	static_assert(sizeof(bhkWorldObject) == 0x28);
}