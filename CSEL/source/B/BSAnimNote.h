#pragma once

#include "../N/NiObject.h"

namespace ConsoleRE
{
	class BSAnimNote : public NiObject
	{
	public:
		~BSAnimNote() override = 0;

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;

		// add
		virtual void Unk_38(void);
	public:
	};
}