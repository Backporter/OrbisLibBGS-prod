#include "../Enchantment/PapyrusExtEnchantment.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/E/EnchantmentItem.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/B/BGSListForm.h"

#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/E/Effect.h"

namespace PapyrusExtEnchantment
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t		GetMagicEffectCount(EnchantmentItem* base)
	{
		if (base)
		{
			return base->effects.m_size;
		}

		return 0;
	}

	float			GetMagicEffectMagnitudeFromIndex(EnchantmentItem* base, uint32_t val)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				return f->GetMagnitude();
			}
		}

		return 0.0f;
	}
	
	uint32_t		GetEffectAreaIndex(EnchantmentItem* base, uint32_t val)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				return f->GetArea();
			}
		}

		return 0;
	}

	uint32_t		GetEffectDurationIndex(EnchantmentItem* base, uint32_t val)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				return f->GetDuration();
			}
		}

		return 0;
	}
	
	EffectSetting*	GetEffectEffectIndex(EnchantmentItem* base, uint32_t val)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				return f->baseEffect;
			}
		}

		return NULL;
	}

	// no impl yet
	uint32_t		GetEffectconstindex(EnchantmentItem* base)
	{
		if (!base)
			return 0;

		Effect* pEI = base->GetCostliestEffectItem(5);
		return pEI ? base->effects.Get(pEI) : 0;
	}

	void			SetEffectMagnitudeIndex(EnchantmentItem* base, uint32_t val, float dstval)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				f->SetMagnitude(dstval);
			}
		}
	}

	void			SetEffectAreaIndex(EnchantmentItem* base, uint32_t val, uint32_t dstval)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				f->SetArea(dstval);
			}
		}
	}

	void			SetEffectDurationIndex(EnchantmentItem* base, uint32_t val, uint32_t dstval)
	{
		if (base)
		{
			auto f = base->effects[val];
			if (f)
			{
				f->SetDuration(dstval);
			}
		}
	}
	
	EnchantmentItem* GetBaseEnchantment(EnchantmentItem* base)
	{
		if (base)
		{
			return base->data.baseEnchantment;
		}

		return NULL;
	}

	BGSListForm*	GetListForm(EnchantmentItem* base)
	{
		if (base)
		{
			return base->data.wornRestrictions;
		}

		return NULL;
	}

	void			SetListForm(EnchantmentItem* base, BGSListForm* list)
	{
		if (base)
		{
			base->data.wornRestrictions = list;
		}
	}

	bool			RegisterEnchantment(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetMagicEffectCount),						EnchantmentItem, uint32_t>					("GetNumEffects",		    "Enchantment", GetMagicEffectCount));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetMagicEffectMagnitudeFromIndex),			EnchantmentItem, float, uint32_t>			("GetNthEffectMagnitude",   "Enchantment", GetMagicEffectMagnitudeFromIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectAreaIndex),						EnchantmentItem, uint32_t, uint32_t>		("GetNthEffectArea",	    "Enchantment", GetEffectAreaIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectDurationIndex),					EnchantmentItem, uint32_t, uint32_t>		("GetNthEffectDuration",    "Enchantment", GetEffectDurationIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectEffectIndex),						EnchantmentItem, EffectSetting*, uint32_t>  ("GetNthEffectMagicEffect", "Enchantment", GetEffectEffectIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectconstindex),						EnchantmentItem, uint32_t>					("GetCostliestEffectIndex", "Enchantment", GetEffectconstindex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetBaseEnchantment),						EnchantmentItem, EnchantmentItem*>			("GetBaseEnchantment",	    "Enchantment", GetBaseEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetListForm),								EnchantmentItem, BGSListForm*>				("GetKeywordRestrictions",  "Enchantment", GetListForm));
	    VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetEffectMagnitudeIndex),					EnchantmentItem, void, uint32_t, float>		("SetNthEffectMagnitude",   "Enchantment", SetEffectMagnitudeIndex));
	    VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetEffectAreaIndex),						EnchantmentItem, void, uint32_t, uint32_t>  ("SetNthEffectArea",	    "Enchantment", SetEffectAreaIndex));
	    VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetEffectDurationIndex),					EnchantmentItem, void, uint32_t, uint32_t>  ("SetNthEffectDuration",    "Enchantment", SetEffectDurationIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetListForm),								EnchantmentItem, void, BGSListForm*>        ("SetKeywordRestrictions",  "Enchantment", SetListForm));

		VM->SetCallableFromTasklets("Enchantment", "GetNumEffects",				true);
		VM->SetCallableFromTasklets("Enchantment", "GetNthEffectMagnitude",		true);
		VM->SetCallableFromTasklets("Enchantment", "GetNthEffectArea",			true);
		VM->SetCallableFromTasklets("Enchantment", "GetNthEffectDuration",		true);
		VM->SetCallableFromTasklets("Enchantment", "GetNthEffectMagicEffect",	true);
		VM->SetCallableFromTasklets("Enchantment", "GetCostliestEffectIndex",	true);
		VM->SetCallableFromTasklets("Enchantment", "GetBaseEnchantment",		true);
		VM->SetCallableFromTasklets("Enchantment", "SetNthEffectMagnitude",		true);
		VM->SetCallableFromTasklets("Enchantment", "SetNthEffectArea",			true);
		VM->SetCallableFromTasklets("Enchantment", "SetNthEffectDuration",		true);
		
		return true;
	}
}