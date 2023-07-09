#pragma once

#include "../N/NiIntegerExtraData.h"

namespace ConsoleRE
{
	class BSXFlags : public NiIntegerExtraData
	{
	public:
		~BSXFlags() override;

		// override (NiIntegerExtraData)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;

		uint32_t GetFlags() const;
		void	 SetFlags(uint32_t a_flags);
	public:
	};
	static_assert(sizeof(BSXFlags) == 0x20);
}