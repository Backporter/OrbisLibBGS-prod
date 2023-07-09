#pragma once

#include "../N/NiProperty.h"

namespace ConsoleRE
{
	class NiShadeProperty : public NiProperty
	{
	public:
		virtual ~NiShadeProperty();

		// override (NiProperty)
		virtual const NiRTTI* GetRTTI() const override;
		virtual NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		virtual void          LoadBinary(NiStream& a_stream) override;
		virtual void          LinkObject(NiStream& a_stream) override;
		virtual bool          RegisterStreamables(NiStream& a_stream) override;
		virtual void          SaveBinary(NiStream& a_stream) override;
		virtual bool          IsEqual(NiObject* a_object) override;
		virtual Type          GetType() const override;

		// add
		virtual void Unk_27(void);  // 27 - { return 1; }
		virtual void Unk_28(void);  // 28 - { return 1; }
		virtual void Unk_29(void);  // 29 - { return; }
	public:
	};
	static_assert(sizeof(NiShadeProperty) == 0x30);
}