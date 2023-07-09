#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct CombatStyleGeneralData
	{
		float offensiveMult;
		float defensiveMult;
		float groupOffensiveMult;
		float meleeScoreMult;
		float magicScoreMult;
		float rangedScoreMult;
		float shoutScoreMult;
		float unarmedScoreMult;
		float staffScoreMult;
		float avoidThreatChance;
	};
	static_assert(sizeof(CombatStyleGeneralData) == 0x28);

	struct CombatStyleMeleeData
	{
		float attackIncapacitatedMult;
		float powerAttackIncapacitatedMult;
		float powerAttackBlockingMult;
		float bashMult;
		float bashRecoilMult;
		float bashAttackMult;
		float bashPowerAttackMult;
		float specialAttackMult;
	};
	static_assert(sizeof(CombatStyleMeleeData) == 0x20);

	struct CombatStyleCloseRangeData
	{
		float circleMult;
		float fallbackMult;
		float flankDistanceMult;
		float stalkTimeMult;
	};
	static_assert(sizeof(CombatStyleCloseRangeData) == 0x10);

	struct CombatStyleLongRangeData
	{
		float strafeMult;
	};
	static_assert(sizeof(CombatStyleLongRangeData) == 0x4);

	struct CombatStyleFlightData
	{
		float hoverChance;
		float diveBombChance;
		float groundAttackChance;
		float hoverTimeMult;
		float groundAttackTimeMult;
		float perchAttackChance;
		float perchAttackTimeMult;
		float flyingAttackChance;
	};
	static_assert(sizeof(CombatStyleFlightData) == 0x20);

	class TESCombatStyle : public TESForm
	{
	public:
		static constexpr int TypeID = 80;
	public:
		~TESCombatStyle() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		CombatStyleGeneralData                generalData;
		CombatStyleMeleeData                  meleeData;
		CombatStyleCloseRangeData             closeRangeData;
		CombatStyleLongRangeData              longRangeData;
		CombatStyleFlightData                 flightData;
		uint32_t							  flags;
	};
	static_assert(sizeof(TESCombatStyle) == 0xA0);
}