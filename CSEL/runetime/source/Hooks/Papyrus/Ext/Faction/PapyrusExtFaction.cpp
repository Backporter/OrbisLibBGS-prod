#include "../Faction/PapyrusExtFaction.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESFaction.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/B/BGSListForm.h"

namespace PapyrusExtFaction
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool IsFactionFlagSet(TESFaction* form, uint32_t flag)
	{
		if (form)
		{
			return ((form->data.flags & flag) == flag);
		}

		return false;
	}

	void SetFactionFlag(TESFaction* form, uint32_t flag)
	{
		if (form)
		{
			form->data.flags |= flag;
		}
	}

	void ClearFactionFlag(TESFaction* form, uint32_t flag)
	{
		if (form)
		{
			form->data.flags &= ~flag;
		}
	}

	bool OnlyBuysStolenItems(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.vendorValues.buysStolen == 1;
		}

		return false;
	}

	void SetOnlyBuysStolenItems(TESFaction* form, bool buystolen)
	{
		if (form)
		{
			form->vendorData.vendorValues.buysStolen = (buystolen ? 1 : 0);
		}
	}

	uint32_t GetVendorStartHour(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.vendorValues.startHour;
		}
		
		return 0;
	}

	void SetVendorStartHour(TESFaction* form, uint32_t hour)
	{
		if (form)
		{
			if (hour > USHRT_MAX)
			{
				hour = USHRT_MAX;
			}

			form->vendorData.vendorValues.startHour = hour;
		}
	}

	uint32_t GetVendorEndHour(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.vendorValues.endHour;
		}
		
		return 0;
	}

	void SetVendorEndHour(TESFaction* form, uint32_t hour)
	{
		if (form)
		{
			if (hour > USHRT_MAX)
			{
				hour = USHRT_MAX;
			}

			form->vendorData.vendorValues.endHour = hour;
		}
	}

	uint32_t GetVendorRadius(TESFaction* form)
	{
		if (form) 
		{ 
			return form->vendorData.vendorValues.locationRadius;
		}
		
		return 0;
	}

	void SetVendorRadius(TESFaction* form, uint32_t radius)
	{
		if (form)
		{
			if (radius > USHRT_MAX)
			{
				radius = USHRT_MAX;
			}

			form->vendorData.vendorValues.locationRadius = radius;
		}
	}

	TESObjectREFR * GetMerchantContainer(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.merchantContainer;
		}
		
		return NULL;
	}

	void SetMerchantContainer(TESFaction* form, TESObjectREFR * reference)
	{
		if (form && reference)
		{
			form->vendorData.merchantContainer = reference;
		}
	}

	bool IsNotSellBuy(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.vendorValues.notBuySell == 1;
		}
		
		return false;
	}

	void SetNotSellBuy(TESFaction* form, bool notSellBuy)
	{
		if (form)
		{
			form->vendorData.vendorValues.notBuySell = (notSellBuy ? 1 : 0);
		}
	}

	BGSListForm * GetBuySellList(TESFaction* form)
	{
		if (form)
		{
			return form->vendorData.vendorSellBuyList;
		}
		
		return NULL;
	}

	void SetBuySellList(TESFaction* form, BGSListForm * vendorList)
	{
		if (form && vendorList)
		{
			form->vendorData.vendorSellBuyList = vendorList;
		}
	}

	bool RegisterFaction(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsFactionFlagSet),       TESFaction, bool, uint32_t>      ("IsFactionFlagSet",       "Faction", IsFactionFlagSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFactionFlag),         TESFaction, void, uint32_t>      ("SetFactionFlag",         "Faction", SetFactionFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ClearFactionFlag),       TESFaction, void, uint32_t>      ("ClearFactionFlag",       "Faction", ClearFactionFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(OnlyBuysStolenItems),    TESFaction, bool>                ("OnlyBuysStolenItems",    "Faction", OnlyBuysStolenItems));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetOnlyBuysStolenItems), TESFaction, void, bool>          ("SetOnlyBuysStolenItems", "Faction", SetOnlyBuysStolenItems));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetVendorStartHour),     TESFaction, uint32_t>            ("GetVendorStartHour",     "Faction", GetVendorStartHour));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetVendorStartHour),     TESFaction, void, uint32_t>      ("SetVendorStartHour",     "Faction", SetVendorStartHour));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetVendorEndHour),       TESFaction, uint32_t>            ("GetVendorEndHour",       "Faction", GetVendorEndHour));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetVendorEndHour),       TESFaction, void, uint32_t>      ("SetVendorEndHour",       "Faction", SetVendorEndHour));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetVendorRadius),        TESFaction, uint32_t>            ("GetVendorRadius",        "Faction", GetVendorRadius));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetVendorRadius),        TESFaction, void, uint32_t>      ("SetVendorRadius",        "Faction", SetVendorRadius));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMerchantContainer),   TESFaction, TESObjectREFR*>      ("GetMerchantContainer",   "Faction", GetMerchantContainer));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMerchantContainer),   TESFaction, void, TESObjectREFR*>("SetMerchantContainer",   "Faction", SetMerchantContainer));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsNotSellBuy),           TESFaction, bool>                ("IsNotSellBuy",           "Faction", IsNotSellBuy));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNotSellBuy),          TESFaction, void, bool>          ("SetNotSellBuy",          "Faction", SetNotSellBuy));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetBuySellList),         TESFaction, BGSListForm*>        ("GetBuySellList",         "Faction", GetBuySellList));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetBuySellList),         TESFaction, void, BGSListForm*>  ("SetBuySellList",         "Faction", SetBuySellList));

		return true;
	}
}