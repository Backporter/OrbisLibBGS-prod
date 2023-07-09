#pragma once

#include "../B/bhkRefObject.h"

namespace ConsoleRE
{
	class ahkpWorld;
	class hkpWorld;
	class bhkWorld;

	class bhkSerializable : public bhkRefObject
	{
	public:
		~bhkSerializable() override;

		// override (bhkRefObject)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
	public:
		bhkSerializable* serializable;
	};
	static_assert(sizeof(bhkSerializable) == 0x20);
}