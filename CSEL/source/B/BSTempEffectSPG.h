#pragma once

#include "../B/BSTempEffect.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BGSShaderParticleGeometryData;
	class NiAVObject;

	class BSTempEffectSPG : public BSTempEffect
	{
	public:
		~BSTempEffectSPG() override;

		const NiRTTI*    GetRTTI() const override;
		void             Detach() override;
		bool             Update(float a_arg1) override;
		uint32_t		 GetType() const override;
		void             SaveGame(BGSSaveGameBuffer* a_buf) override;
		void             LoadGame(BGSLoadGameBuffer* a_buf) override;
		void             FinishLoadGame(BGSLoadGameBuffer* a_buf) override;

	public:
		BGSShaderParticleGeometryData* data;
		NiPointer<NiAVObject>          spg3D;
		float                          unk40;
		float                          unk44;
		bool                           unk48;
		uint8_t						   pad49;
		uint16_t					   pad4A;
	};
	static_assert(sizeof(BSTempEffectSPG) == 0x48);
}