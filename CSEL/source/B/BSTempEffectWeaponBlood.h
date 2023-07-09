#pragma once

#include "../B/BSTempEffect.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiAVObject;

	class BSTempEffectWeaponBlood : public BSTempEffect
	{
	public:
		~BSTempEffectWeaponBlood() override;

		// override (BSTempEffect)
		bool	 Update(float a_arg1) override;
		uint32_t GetType() const override;
	public:
		NiPointer<NiAVObject> weapon3D;
		float                 alphaThreshold;
	};
	static_assert(sizeof(BSTempEffectWeaponBlood) == 0x38);
}