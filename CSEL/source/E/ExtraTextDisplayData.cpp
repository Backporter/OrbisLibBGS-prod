#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraTextDisplayData.h"

namespace ConsoleRE
{
	ExtraTextDisplayData::ExtraTextDisplayData() : 
		BSExtraData(), 
		displayName(""), 
		displayNameText(nullptr), 
		ownerQuest(nullptr), 
		ownerInstance(-1), 
		temperFactor(1.0F), 
		customNameLength(0), 
		pad32(0), 
		pad34(0)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraTextDisplayData:.data.rel.ro", 0x1D1E328);
		*((uintptr_t*)this) = vtbl.address();
	}

	ExtraTextDisplayData::ExtraTextDisplayData(const char* a_name) : 
		BSExtraData(), 
		displayName(""), 
		displayNameText(nullptr), 
		ownerQuest(nullptr), 
		ownerInstance(-1), 
		temperFactor(1.0F), 
		customNameLength(0), 
		pad32(0), 
		pad34(0)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraTextDisplayData:.data.rel.ro", 0x1D1E328);
		*((uintptr_t*)this) = vtbl.address();
		SetName(a_name);
	}

	ExtraTextDisplayData::ExtraTextDisplayData(TESBoundObject* a_baseObject, float a_temperFactor) : 
		BSExtraData(), 
		displayName(""), 
		displayNameText(nullptr), 
		ownerQuest(nullptr), 
		ownerInstance(-1), 
		temperFactor(1.0F), 
		customNameLength(0), 
		pad32(0), 
		pad34(0)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraTextDisplayData:.data.rel.ro", 0x1D1E328);
		*((uintptr_t*)this) = vtbl.address();
		GetDisplayName(a_baseObject, a_temperFactor);
	}


	uint32_t ExtraTextDisplayData::GetType() const
	{
		return TypeID;
	}


	const char* ExtraTextDisplayData::GetDisplayName(TESBoundObject* a_baseObject, float a_temperFactor)
	{
		using func_t = decltype(&ExtraTextDisplayData::GetDisplayName);
		Relocation<func_t> func("", 0x7F770);
		return func(this, a_baseObject, a_temperFactor);
	}

	bool ExtraTextDisplayData::IsPlayerSet()
	{
		return ownerInstance == -2;
	}

	void ExtraTextDisplayData::SetName(const char* a_name)
	{
		if (displayNameText)
		{
			return;
		}

		displayName			= a_name;
		customNameLength	= static_cast<uint16_t>(strlen(displayName.c_str()));
		ownerInstance		= -2;
		temperFactor		= 1.0F;
	}
}