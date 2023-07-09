#include "../INI/PapyrusExtINI.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/I/INISettingCollection.h"

namespace PapyrusExtINI
{
	using namespace ConsoleRE;

	float	      PapyrusGetINIFloat(StaticFunctionTag*, BSFixedString name)
	{
		auto singleton = ConsoleRE::INISettingCollection::GetSingleton();
		auto setting = singleton ? singleton->GetSetting(name.m_data) : nullptr;
		return setting ? setting->GetFloat() : 0.0f;
	}

	uint32_t      PapyrusGetUInt32(StaticFunctionTag*, BSFixedString name)
	{
		auto singleton = ConsoleRE::INISettingCollection::GetSingleton();
		auto setting = singleton ? singleton->GetSetting(name.m_data) : nullptr;
		return setting ? setting->GetUInt32(): 0;
	}

	bool		  PapyrusGetINIBoolean(StaticFunctionTag*, BSFixedString name)
	{
		auto singleton = ConsoleRE::INISettingCollection::GetSingleton();
		auto setting = singleton ? singleton->GetSetting(name.m_data) : nullptr;
		return setting ? setting->GetBool() : false;
	}

	BSFixedString PapyrusGetINIString(StaticFunctionTag*, BSFixedString name)
	{
		auto singleton = ConsoleRE::INISettingCollection::GetSingleton();
		auto setting = singleton ? singleton->GetSetting(name.m_data) : nullptr;
		return setting ? setting->GetString() : "";
	}

	bool RegisterINI(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(PapyrusGetINIFloat),   ConsoleRE::StaticFunctionTag, float,	     BSFixedString>("GetINIFloat",  "Utility", PapyrusGetINIFloat));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(PapyrusGetUInt32),	    ConsoleRE::StaticFunctionTag, uint32_t,	     BSFixedString>("GetINIInt",    "Utility", PapyrusGetUInt32));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(PapyrusGetINIBoolean), ConsoleRE::StaticFunctionTag, bool,		     BSFixedString>("GetINIBool",   "Utility", PapyrusGetINIBoolean));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(PapyrusGetINIString),  ConsoleRE::StaticFunctionTag, BSFixedString, BSFixedString>("GetINIString", "Utility", PapyrusGetINIString));

		VM->SetCallableFromTasklets("Utility", "GetINIFloat",  true);
		VM->SetCallableFromTasklets("Utility", "GetINIInt",    true);
		VM->SetCallableFromTasklets("Utility", "GetINIBool",   true);
		VM->SetCallableFromTasklets("Utility", "GetINIString", true);

		return true;
	}
}