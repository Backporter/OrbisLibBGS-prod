#include "../CombatStyle/PapyrusExtCombatStyle.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESCombatStyle.h"

namespace PapyrusExtCombatStyle
{
	// I really hate doing this...
	using namespace ConsoleRE;

	float GetOffensiveMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.offensiveMult : 0.0;
	}

	void SetOffensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.offensiveMult = nuVal;
		}
	}

	float GetDefensiveMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.defensiveMult : 0.0;
	}

	void SetDefensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.defensiveMult = nuVal;
		}
	}

	float GetGroupOffensiveMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.groupOffensiveMult : 0.0;
	}

	void SetGroupOffensiveMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.groupOffensiveMult = nuVal;
		}
	}

	float GetmeleeScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.meleeScoreMult : 0.0;
	}

	void SetmeleeScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) 
		{
			thisCombatStyle->generalData.meleeScoreMult = nuVal;
		}
	}

	float GetrangedScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.rangedScoreMult : 0.0;
	}

	void SetrangedScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) 
		{
			thisCombatStyle->generalData.rangedScoreMult = nuVal;
		}
	}

	float GetmagicScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.magicScoreMult : 0.0;
	}

	void SetmagicScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.magicScoreMult = nuVal;
		}
	}

	float GetshoutScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.shoutScoreMult : 0.0;
	}

	void SetshoutScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.shoutScoreMult = nuVal;
		}
	}

	float GetstaffScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.staffScoreMult : 0.0;
	}

	void SetstaffScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.staffScoreMult = nuVal;
		}
	}

	float GetunarmedScoreMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.unarmedScoreMult : 0.0;
	}

	void SetunarmedScoreMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.unarmedScoreMult = nuVal;
		}
	}

	float GetAvoidThreatChance(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->generalData.avoidThreatChance : 0.0;
	}

	void SetAvoidThreatChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->generalData.avoidThreatChance = nuVal;
		}
	}

	float GetMeleeattackIncapacitatedMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.attackIncapacitatedMult : 0.0;
	}

	void SetMeleeattackIncapacitatedMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.attackIncapacitatedMult = nuVal;
		}
	}

	float GetMeleepowerAttackIncapacitatedMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.powerAttackIncapacitatedMult : 0.0;
	}

	void SetMeleepowerAttackIncapacitatedMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.powerAttackIncapacitatedMult = nuVal;
		}
	}

	float GetMeleePowerAttackBlockingMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.powerAttackBlockingMult : 0.0;
	}

	void SetMeleePowerAttackBlockingMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.powerAttackBlockingMult = nuVal;
		}
	}

	float GetMeleeBashMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.bashMult : 0.0;
	}

	void SetMeleeBashMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.bashMult = nuVal;
		}
	}

	float GetMeleebashRecoilMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.bashRecoilMult : 0.0;
	}

	void SetMeleebashRecoilMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.bashRecoilMult = nuVal;
		}
	}

	float GetMeleeBashAttackMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.bashAttackMult : 0.0;
	}

	void SetMeleeBashAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.bashAttackMult = nuVal;
		}
	}

	float GetMeleeBashPowerAttackMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.bashPowerAttackMult : 0.0;
	}

	void SetMeleeBashPowerAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.bashPowerAttackMult = nuVal;
		}
	}

	float GetMeleeSpecialAttackMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->meleeData.specialAttackMult : 0.0;
	}

	void SetMeleeSpecialAttackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->meleeData.specialAttackMult = nuVal;
		}
	}

	float GetCloseRangecircleMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->closeRangeData.circleMult : 0.0;
	}

	void SetCloseRangecircleMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRangeData.circleMult = nuVal;
		}
	}

	float GetCloseRangefallbackMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->closeRangeData.fallbackMult : 0.0;
	}

	void SetCloseRangefallbackMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRangeData.fallbackMult = nuVal;
		}
	}

	float GetCloseRangeflankDistanceMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->closeRangeData.flankDistanceMult : 0.0;
	}

	void SetCloseRangeflankDistanceMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRangeData.flankDistanceMult = nuVal;
		}
	}

	float GetCloseRangestalkTimeMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->closeRangeData.stalkTimeMult : 0.0;
	}

	void SetCloseRangestalkTimeMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->closeRangeData.stalkTimeMult = nuVal;
		}
	}

	float GetLongRangeStrafeMult(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->longRangeData.strafeMult : 0.0;
	}

	void SetLongRangeStrafeMult(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->longRangeData.strafeMult = nuVal;
		}
	}


	float GetFlightHoverChance(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->flightData.hoverChance : 0.0;
	}

	void SetFlightHoverChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flightData.hoverChance = nuVal;
		}
	}

	float GetFlightDiveBombChance(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->flightData.diveBombChance : 0.0;
	}

	void SetFlightDiveBombChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flightData.diveBombChance = nuVal;
		}
	}

	float GetFlightFlyingAttackChance(TESCombatStyle* thisCombatStyle)
	{
		return (thisCombatStyle) ? thisCombatStyle->flightData.flyingAttackChance : 0.0;
	}

	void SetFlightFlyingAttackChance(TESCombatStyle* thisCombatStyle, float nuVal)
	{
		if (thisCombatStyle) {
			thisCombatStyle->flightData.flyingAttackChance = nuVal;
		}
	}

	bool GetAllowDualWielding(TESCombatStyle* thisCombatStyle)
	{
		if (!thisCombatStyle)
			return false;

		return (thisCombatStyle->flags & 4) == 4 ? true : false;
	}

	void SetAllowDualWielding(TESCombatStyle* thisCombatStyle, bool bAllow)
	{
		if (thisCombatStyle) 
		{
			if (bAllow)
				thisCombatStyle->flags |= 4;
			else
				thisCombatStyle->flags &= ~4;
		}
	}

	bool RegisterCombatStyle(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetOffensiveMult),                          TESCombatStyle, float>       ("GetOffensiveMult",						"CombatStyle", GetOffensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetDefensiveMult),                          TESCombatStyle, float>       ("GetDefensiveMult",						"CombatStyle", GetDefensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetGroupOffensiveMult),                     TESCombatStyle, float>       ("GetGroupOffensiveMult",					"CombatStyle", GetGroupOffensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetAvoidThreatChance),                      TESCombatStyle, float>       ("GetAvoidThreatChance",					"CombatStyle", GetAvoidThreatChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetmeleeScoreMult),                         TESCombatStyle, float>       ("GetmeleeScoreMult",						"CombatStyle", GetmeleeScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetrangedScoreMult),                        TESCombatStyle, float>       ("GetrangedScoreMult",					"CombatStyle", GetrangedScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetmagicScoreMult),                         TESCombatStyle, float>       ("GetmagicScoreMult",						"CombatStyle", GetmagicScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetshoutScoreMult),                         TESCombatStyle, float>       ("GetshoutScoreMult",						"CombatStyle", GetshoutScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetstaffScoreMult),                         TESCombatStyle, float>       ("GetstaffScoreMult",						"CombatStyle", GetstaffScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetunarmedScoreMult),                       TESCombatStyle, float>       ("GetunarmedScoreMult",					"CombatStyle", GetunarmedScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetOffensiveMult),                          TESCombatStyle, void, float> ("SetOffensiveMult",						"CombatStyle", SetOffensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetDefensiveMult),                          TESCombatStyle, void, float> ("SetDefensiveMult",						"CombatStyle", SetDefensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetGroupOffensiveMult),                     TESCombatStyle, void, float> ("SetGroupOffensiveMult",					"CombatStyle", SetGroupOffensiveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetAvoidThreatChance),                      TESCombatStyle, void, float> ("SetAvoidThreatChance",					"CombatStyle", SetAvoidThreatChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetmeleeScoreMult),                         TESCombatStyle, void, float> ("SetmeleeScoreMult",						"CombatStyle", SetmeleeScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetrangedScoreMult),                        TESCombatStyle, void, float> ("SetrangedScoreMult",					"CombatStyle", SetrangedScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetmagicScoreMult),                         TESCombatStyle, void, float> ("SetmagicScoreMult",						"CombatStyle", SetmagicScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetshoutScoreMult),                         TESCombatStyle, void, float> ("SetshoutScoreMult",						"CombatStyle", SetshoutScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetstaffScoreMult),                         TESCombatStyle, void, float> ("SetstaffScoreMult",						"CombatStyle", SetstaffScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetunarmedScoreMult),                       TESCombatStyle, void, float> ("SetunarmedScoreMult",					"CombatStyle", SetunarmedScoreMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleeattackIncapacitatedMult),           TESCombatStyle, float>       ("GetMeleeattackIncapacitatedMult",		"CombatStyle", GetMeleeattackIncapacitatedMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleepowerAttackIncapacitatedMult),      TESCombatStyle, float>       ("GetMeleepowerAttackIncapacitatedMult",	"CombatStyle", GetMeleepowerAttackIncapacitatedMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleePowerAttackBlockingMult),           TESCombatStyle, float>       ("GetMeleePowerAttackBlockingMult",		"CombatStyle", GetMeleePowerAttackBlockingMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleeBashMult),                          TESCombatStyle, float>       ("GetMeleeBashMult",						"CombatStyle", GetMeleeBashMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleebashRecoilMult),                    TESCombatStyle, float>       ("GetMeleebashRecoilMult",				"CombatStyle", GetMeleebashRecoilMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleeBashAttackMult),                    TESCombatStyle, float>       ("GetMeleeBashAttackMult",				"CombatStyle", GetMeleeBashAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleeBashPowerAttackMult),               TESCombatStyle, float>       ("GetMeleeBashPowerAttackMult",			"CombatStyle", GetMeleeBashPowerAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMeleeSpecialAttackMult),                 TESCombatStyle, float>       ("GetMeleeSpecialAttackMult",				"CombatStyle", GetMeleeSpecialAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetAllowDualWielding),                      TESCombatStyle, bool>        ("GetAllowDualWielding",					"CombatStyle", GetAllowDualWielding));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleeattackIncapacitatedMult),           TESCombatStyle, void, float> ("SetMeleeattackIncapacitatedMult",		"CombatStyle", SetMeleeattackIncapacitatedMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleepowerAttackIncapacitatedMult),      TESCombatStyle, void, float> ("SetMeleepowerAttackIncapacitatedMult",	"CombatStyle", SetMeleepowerAttackIncapacitatedMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleePowerAttackBlockingMult),           TESCombatStyle, void, float> ("SetMeleePowerAttackBlockingMult",		"CombatStyle", SetMeleePowerAttackBlockingMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleeBashMult),							 TESCombatStyle, void, float> ("SetMeleeBashMult",						"CombatStyle", SetMeleeBashMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleebashRecoilMult),		             TESCombatStyle, void, float> ("SetMeleebashRecoilMult",				"CombatStyle", SetMeleebashRecoilMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleeBashAttackMult),			         TESCombatStyle, void, float> ("SetMeleeBashAttackMult",				"CombatStyle", SetMeleeBashAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleeBashPowerAttackMult),				 TESCombatStyle, void, float> ("SetMeleeBashPowerAttackMult",			"CombatStyle", SetMeleeBashPowerAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMeleeSpecialAttackMult),                 TESCombatStyle, void, float> ("SetMeleeSpecialAttackMult",				"CombatStyle", SetMeleeSpecialAttackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetAllowDualWielding),						 TESCombatStyle, void, bool>  ("SetAllowDualWielding",					"CombatStyle", SetAllowDualWielding));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCloseRangecircleMult),                   TESCombatStyle, float>       ("GetCloseRangecircleMult",				"CombatStyle", GetCloseRangecircleMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCloseRangefallbackMult),                 TESCombatStyle, float>       ("GetCloseRangefallbackMult",				"CombatStyle", GetCloseRangefallbackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCloseRangeflankDistanceMult),            TESCombatStyle, float>       ("GetCloseRangeflankDistanceMult",		"CombatStyle", GetCloseRangeflankDistanceMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCloseRangestalkTimeMult),                TESCombatStyle, float>       ("GetCloseRangestalkTimeMult",			"CombatStyle", GetCloseRangestalkTimeMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCloseRangecircleMult),                   TESCombatStyle, void, float> ("SetCloseRangecircleMult",				"CombatStyle", SetCloseRangecircleMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCloseRangefallbackMult),                 TESCombatStyle, void, float> ("SetCloseRangefallbackMult",				"CombatStyle", SetCloseRangefallbackMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCloseRangeflankDistanceMult),            TESCombatStyle, void, float> ("SetCloseRangeflankDistanceMult",		"CombatStyle", SetCloseRangeflankDistanceMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCloseRangestalkTimeMult),                TESCombatStyle, void, float> ("SetCloseRangestalkTimeMult",			"CombatStyle", SetCloseRangestalkTimeMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLongRangeStrafeMult),                    TESCombatStyle, float>       ("GetLongRangeStrafeMult",				"CombatStyle", GetLongRangeStrafeMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetLongRangeStrafeMult),                    TESCombatStyle, void, float> ("SetLongRangeStrafeMult",				"CombatStyle", SetLongRangeStrafeMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFlightHoverChance),                      TESCombatStyle, float>       ("GetFlightHoverChance",					"CombatStyle", GetFlightHoverChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFlightDiveBombChance),                   TESCombatStyle, float>       ("GetFlightDiveBombChance",				"CombatStyle", GetFlightDiveBombChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFlightFlyingAttackChance),               TESCombatStyle, float>       ("GetFlightFlyingAttackChance",			"CombatStyle", GetFlightFlyingAttackChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFlightHoverChance),                      TESCombatStyle, void, float> ("SetFlightHoverChance",					"CombatStyle", SetFlightHoverChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFlightDiveBombChance),                   TESCombatStyle, void, float> ("SetFlightDiveBombChance",				"CombatStyle", SetFlightDiveBombChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFlightFlyingAttackChance),               TESCombatStyle, void, float> ("SetFlightFlyingAttackChance",			"CombatStyle", SetFlightFlyingAttackChance));

		return true;
	}
}