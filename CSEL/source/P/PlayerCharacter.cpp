#include "../../../OrbisUtil/include/Relocation.h"

#include "../P/PlayerCharacter.h"

#include "../T/TESObjectREFR.h"
#include "../A/ActorValueList.h"

namespace ConsoleRE
{
	int32_t	PlayerCharacter::PlayerSkills::ResolveAdvancedSkillId(int32_t a_value)
	{
		if (a_value - 6 >= 0 && a_value < 18 + 6)
		{
			return a_value - 6;
		}

		return -1;
	}

	float PlayerCharacter::PlayerSkills::GetSkillPoints(BSFixedString a_value, bool a_legendary)
	{
		if (data)
		{
			uint32_t actorValueID = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(a_value.c_str());
			int32_t skillID = ResolveAdvancedSkillId(actorValueID);
			if (skillID != -1)
			{
				if (a_legendary)
				{
					return data->legendaryLevels[skillID];
				}
				else
				{
					return data->skills[skillID].xp;
				}
			}
		}

		return 0.0f;
	}

	void PlayerCharacter::PlayerSkills::SetSkillPoints(BSFixedString a_actorValue, float a_value, bool a_legendary)
	{
		if (data)
		{
			uint32_t actorValueID = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(a_actorValue.c_str());
			int32_t skillID = ResolveAdvancedSkillId(actorValueID);
			if (skillID != -1)
			{
				if (a_legendary)
				{
					data->legendaryLevels[skillID] = a_value;
				}
				else
				{
					data->skills[skillID].xp = a_value;
				}
			}
		}
	}

	void PlayerCharacter::PlayerSkills::SetLevel(uint32_t a_level)
	{
		using func_t = decltype(&PlayerCharacter::PlayerSkills::SetLevel);
		Relocation<func_t> func("", 0x83CB00);
		return func(this, a_level);
	}

	void PlayerCharacter::PlayerSkills::IncrementLegendary(uint32_t a_actorvalue)
	{
		using func_t = decltype(&PlayerCharacter::PlayerSkills::IncrementLegendary);
		Relocation<func_t> func("", 0x83CB60);
		return func(this, a_actorvalue);
	}

	uint32_t PlayerCharacter::PlayerSkills::GetSkillData(uint32_t a_actorvalue, float& a_unk3, float& a_unk4, float& a_unk5, float& a_unk6)
	{
		using func_t = decltype(&PlayerCharacter::PlayerSkills::GetSkillData);
		Relocation<func_t> func("", 0x83CC60);
		return func(this, a_actorvalue, a_unk3, a_unk4, a_unk5, a_unk6);
	}





	PlayerCharacter* PlayerCharacter::GetSingleton()
	{
		Relocation<PlayerCharacter**> Player("", 0x313D910);
		return *Player;
	}

	void PlayerCharacter::ActivatePickRef() 
	{
		using func_t = decltype(&PlayerCharacter::ActivatePickRef);
		Relocation<func_t>	func("", 0x7E89B0);
		return func(this);
	}

	bool PlayerCharacter::AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, int32_t a_number, bool a_fromContainer) 
	{ 
		using func_t = decltype(&PlayerCharacter::AttemptPickpocket);
		Relocation<func_t>  func("", 0x8004F0);
		return func(this, a_containerRef, a_entry, a_number, a_fromContainer);
	}

	bool PlayerCharacter::CenterOnCell(const char* a_cellName) 
	{
		return CenterOnCell_Impl(a_cellName, nullptr); 
	}
	
	bool PlayerCharacter::CenterOnCell(TESObjectCELL* a_cell) 
	{
		return CenterOnCell_Impl(nullptr, a_cell); 
	}

	NiPointer<Actor> PlayerCharacter::GetActorDoingPlayerCommand() const
	{
		
	}

	float PlayerCharacter::GetArmorValue(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetArmorValue);
		Relocation<func_t> func("", 0x7CD700);
		return func(this, a_form);
	}

	float PlayerCharacter::GetDamage(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetDamage);
		Relocation<func_t> func("", 0x7CD970);
		return func(this, a_form);
	}

	NiPointer<TESObjectREFR> PlayerCharacter::GetGrabbedRef()
	{
	}

	uint32_t PlayerCharacter::GetNumTints(uint32_t a_tintType) 
	{
		using func_t = decltype(&PlayerCharacter::GetNumTints);
		Relocation<func_t> func("", 0x803900);
		return func(this, a_tintType);
	}

	TintMask* PlayerCharacter::GetOverlayTintMask(TintMask* a_original)
	{
		if (!UnkA50)
			return nullptr;

		for (int i = 0; i < UnkA40.size(); i++)
		{
			if (UnkA40[i] == a_original)
			{
				return i < UnkA50->size() ? (*UnkA50)[i] : nullptr;
			}
		}

		return nullptr;
	}

	BSTArray<TintMask*>& PlayerCharacter::GetTintList()
	{ 
		return UnkA50 ? *UnkA50 : UnkA40; 
	}

	TintMask* PlayerCharacter::GetTintMask(uint32_t a_tintType, uint32_t a_index)
	{ 
		using func_t = decltype(&PlayerCharacter::GetTintMask);
		Relocation<func_t> func("", 0x803890);
		return func(this, a_tintType, a_index);
	}

	bool PlayerCharacter::HasActorDoingCommand()
	{ 
		return static_cast<bool>(Unk7CC);
	}
	
	bool PlayerCharacter::IsGrabbing()
	{ 
		return static_cast<bool>(Unk800);
	}

	void PlayerCharacter::PlayPickupEvent(TESForm* a_item, TESForm* a_containerOwner, TESObjectREFR* a_containerRef, uint32_t a_eventType)
	{
		using func_t = decltype(&PlayerCharacter::PlayPickupEvent);
		Relocation<func_t> func("", 0x7F0680);
		return func(this, a_item, a_containerOwner, a_containerRef, a_eventType);
	}

	void PlayerCharacter::StartGrabObject()
	{
		using func_t = decltype(&PlayerCharacter::StartGrabObject);
		Relocation<func_t> func("", 0x7F79B0);
		return func(this);
	}

	bool PlayerCharacter::CenterOnCell_Impl(const char* a_cellName, TESObjectCELL* a_cell) 
	{ 
		using func_t = decltype(&PlayerCharacter::CenterOnCell_Impl);
		Relocation<func_t> func("", 0x7E12D0);  
		return func(this, a_cellName, a_cell); 
	}

	void PlayerCharacter::AddSkillExperience(uint32_t a_actorValue, float a_points) 
	{
		using func_t = decltype(&PlayerCharacter::AddSkillExperience);
		Relocation<func_t> func("", 0x7ECBA0);  
		return func(this, a_actorValue, a_points); 
	}

	uint32_t PlayerCharacter::UpdatePlayerTints() 
	{ 
		using func_t = decltype(&PlayerCharacter::UpdatePlayerTints);
		Relocation<func_t> func("", 0xA5CB60);  
		return func(); 
	}
}