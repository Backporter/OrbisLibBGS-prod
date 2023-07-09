#pragma once

#include "../N/NiObjectNET.h"

namespace ConsoleRE
{
	class NiProperty : public NiObjectNET
	{
	public:
		enum class Type
		{
			kAlpha = 0,
			kShade = 1
		};
	public:
		virtual ~NiProperty();

		// override (NiObjectNET)
		virtual const NiRTTI* GetRTTI() const override;
		virtual void          LoadBinary(NiStream& a_stream) override;
		virtual void          LinkObject(NiStream& a_stream) override;
		virtual bool          RegisterStreamables(NiStream& a_stream) override;
		virtual void          SaveBinary(NiStream& a_stream) override;
		virtual bool          IsEqual(NiObject* a_object) override;
		virtual void          ProcessClone(NiCloningProcess& a_cloning) override;

		 // add
		virtual Type GetType() const = 0;
		virtual void Update(float a_time);
	public:
	};
	static_assert(sizeof(NiProperty) == 0x30);
}