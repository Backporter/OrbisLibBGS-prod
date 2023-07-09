#pragma once

#include "../N/NiExtraData.h"

namespace ConsoleRE
{
	class NiIntegerExtraData : public NiExtraData
	{
	public:
		~NiIntegerExtraData() override;

		// override (NiExtraData)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
	public:
		int32_t  value;
		uint32_t pad1C;
	};
	static_assert(sizeof(NiIntegerExtraData) == 0x20);
}