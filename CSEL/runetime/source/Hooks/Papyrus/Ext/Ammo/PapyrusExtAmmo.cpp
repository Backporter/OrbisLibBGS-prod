#include "../Ammo/PapyrusExtAmmo.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSProjectile.h"
#include "../../../../../../source/T/TESAmmo.h"

namespace PapyrusExtAmmo
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool IsBolt(TESAmmo * thisAmmo)
	{
		return (thisAmmo) ? thisAmmo->isBolt() : false;
	}

	BGSProjectile* GetProjectile(TESAmmo * thisAmmo)
	{
		return (thisAmmo) ? thisAmmo->data.projectile : NULL;
	}

	float GetDamage(TESAmmo * thisAmmo)
	{
		return (thisAmmo) ? thisAmmo->data.damage : 0.0f;
	}

	bool RegisterAmmo(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsBolt),        TESAmmo, bool>          ("IsBolt",        "Ammo", IsBolt));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetProjectile), TESAmmo, BGSProjectile*>("GetProjectile", "Ammo", GetProjectile));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetDamage),     TESAmmo, float>         ("GetDamage",     "Ammo", GetDamage));
		
		return true;
	}

}