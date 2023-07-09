#pragma once

#include "../B/BSTSmartPointer.h"
#include "../N/NiShadeProperty.h"

namespace ConsoleRE
{
	class BSShaderMaterial;

	class BSShaderProperty : public NiShadeProperty
	{
	public:
		virtual ~BSShaderProperty();

		// override (NiShadeProperty)
		virtual const NiRTTI* GetRTTI() const override;
		virtual NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		virtual void          LoadBinary(NiStream& a_stream) override;
		virtual void          LinkObject(NiStream& a_stream) override;
		virtual bool          RegisterStreamables(NiStream& a_stream) override;
		virtual void          SaveBinary(NiStream& a_stream) override;
		virtual bool          IsEqual(NiObject* a_object) override;
		virtual void          PostLinkObject(NiStream& a_stream) override;
		virtual void          Unk_27(void) override;
		virtual void          Unk_29(void) override;

		// add
		virtual void Unk_2A(void) = 0;
		virtual void Unk_2B(void);
		virtual void Unk_2C(void);
		virtual void Unk_2D(void);
		virtual void Unk_2E(void);
		virtual void Unk_2F(void);
		virtual void Unk_30(void);
		virtual void Unk_31(void);
		virtual void Unk_32(void);
		virtual void Unk_33(void);
		virtual void Unk_34(void);
		virtual void Unk_35(void);
		virtual void Unk_36(void);
		virtual void Unk_37(void);
		virtual void Unk_38(void);
		virtual bool AcceptsEffectData() const;
		virtual void Unk_3A(void);
		virtual void Unk_3B(void);
		virtual void Unk_3C(void);
		virtual void Unk_3D(void);
		virtual void Unk_3E(void);
	public:
		float													alpha;
		int32_t													lastRenderPassState;
		uint64_t												flags;
		void*													unk40;
		uint64_t												unk48;
		void*													unk50;
		uint64_t												unk58;
		uint64_t												unk60;
		void*													effectData;
		uint64_t												unk70;
		BSShaderMaterial*										material;
		uint64_t												unk80;
		uint64_t												Unk88;
	};
	static_assert(sizeof(BSShaderProperty) == 0x90);
}