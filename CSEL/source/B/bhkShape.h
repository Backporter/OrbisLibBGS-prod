#pragma once

#include "../B/bhkSerializable.h"

namespace ConsoleRE
{
	class bhkShape : public bhkSerializable
	{
	public:
		~bhkShape() override;

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
	public:
		uint64_t unk20;
	};
	static_assert(sizeof(bhkShape) == 0x28);
}