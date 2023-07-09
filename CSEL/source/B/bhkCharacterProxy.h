#pragma once

#include "../B/bhkCharacterPointCollector.h"
#include "../B/bhkSerializable.h"

namespace ConsoleRE
{
	class bhkCharacterProxy : public bhkSerializable
	{
	public:
		~bhkCharacterProxy() override;

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
	public:
		bhkCharacterPointCollector ignoredCollisionStartCollector;
	};
	static_assert(sizeof(bhkCharacterProxy) == 0x260);
}