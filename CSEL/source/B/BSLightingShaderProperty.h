#pragma once

#include "../B/BSShaderProperty.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class NiColor;

	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		struct Data
		{
			uint64_t unk00;
			uint64_t unk08;
		};
		static_assert(sizeof(Data) == 0x10);
	public:
		~BSLightingShaderProperty() override;

		// override (BSShaderProperty)
		const NiRTTI* GetRTTI() const override;                           
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  
		void          LoadBinary(NiStream& a_stream) override;            
		void          LinkObject(NiStream& a_stream) override;            
		bool          RegisterStreamables(NiStream& a_stream) override;   
		void          SaveBinary(NiStream& a_stream) override;            
		bool          IsEqual(NiObject* a_object) override;               
		void          PostLinkObject(NiStream& a_stream) override;        
		void          Unk_27(void) override;                              
		void          Unk_28(void) override;                              
		void          Unk_2A(void) override;                              
		void          Unk_2B(void) override;                              
		void          Unk_2C(void) override;                              
		void          Unk_2D(void) override;                              
		void          Unk_2F(void) override;                              
		void          Unk_30(void) override;                              
		void          Unk_31(void) override;                              
		void          Unk_32(void) override;                              
		void          Unk_33(void) override;                              
		void          Unk_34(void) override;                              
		void          Unk_35(void) override;                              
		void          Unk_37(void) override;                              
		bool          AcceptsEffectData() const override;                 
		void          Unk_3B(void) override;                              
		void          Unk_3D(void) override;                              
		void          Unk_3E(void) override;                              
	public:
		Data            unk090[3];
		Data            unk0C0;
		Data            unk0D0;
		Data            unk0D8;
		uint64_t		unk0E8;
		uint64_t		Unk0F8;
		uint64_t		Unk100;
		uint64_t		Unk108;
		uint64_t		Unk110;
		uint64_t		Unk118;
		uint64_t		Unk120;
		uint64_t		Unk128;
		NiColor*        emissiveColor;
		float           emissiveMult;
		uint32_t		unk13C;
		uint64_t		unk140;
		uint64_t		unk148;
		uint64_t		unk150;
		uint64_t		unk158;
		uint64_t		unk160;
		uint64_t		unk168;
		uint64_t		unk170;
		BSTArray<void*> unk178;
		uint64_t		unk188;
		uint64_t		unk190;
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0x198);
}