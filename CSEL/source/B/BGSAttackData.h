#pragma once

#include "../B/BSFixedString.h"
#include "../F/FormTypes.h"
#include "../N/NiRefObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	struct AttackData
	{
	public:
		enum class AttackFlag
		{
			kNone = 0,
			kIgnoreWeapon = 1 << 0,
			kBashAttack = 1 << 1,
			kPowerAttack = 1 << 2,
			kChargeAttack = 1 << 3,
			kRotatingAttack = 1 << 4,
			kContinuousAttack = 1 << 5,
			kOverrideData = 1 << 31
		};
	public:
		float                                       damageMult;
		float                                       attackChance;
		SpellItem*                                  attackSpell;
		uint32_t									flags;
		float                                       attackAngle;
		float                                       strikeAngle;
		float                                       staggerOffset;
		BGSKeyword*                                 attackType;
		float                                       knockDown;
		float                                       recoveryTime;
		float                                       staminaMult;
		uint32_t									pad34;
	};
	static_assert(sizeof(AttackData) == 0x38);

	class BGSAttackData : public NiRefObject
	{
	public:
		~BGSAttackData() override;

		bool IsLeftAttack() const;
	public:
		BSFixedString event;
		AttackData    data;
	};
}