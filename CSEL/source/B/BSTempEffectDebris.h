#pragma once

#include "../B/BSTempEffect.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSTempEffectDebris : public BSTempEffect
	{
	public:
		~BSTempEffectDebris() override;

		// override (BSTempEffect)
		const NiRTTI*    GetRTTI() const override;
		bool             Update(float a_arg1) override;
		NiAVObject*      Get3D() const override;
		uint32_t		 GetType() const override;
	public:
		NiPointer<NiAVObject> debris3D;
		const char*           debrisFileName;
		bool                  unk40;
		uint8_t				  unk41;
		uint8_t				  pad42;
		uint8_t				  pad43;
		uint32_t			  pad44;
	};
	static_assert(sizeof(BSTempEffectDebris) == 0x40);
}