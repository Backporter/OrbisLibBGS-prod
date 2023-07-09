#include "../Forms/PapyrusExtForms.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#if defined(__OPENORBIS__)
#include <orbis/Rtc.h>
#include <orbis/libkernel.h>
typedef TimeTable SceRtcDateTime;
#elif defined(__ORBIS__)
#include <rtc.h>
#include <kernel.h>
#include <wchar.h>
#include <string>
#endif

#include "../../../../../../source/B/BGSSoundDescriptorForm.h"
#include "../../../../../../source/A/ActorValueInfo.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/B/BGSArtObject.h"
#include "../../../../../../source/B/BGSColorForm.h"
#include "../../../../../../source/T/TESCombatStyle.h"
#include "../../../../../../source/B/BGSDefaultObjectManager.h"
#include "../../../../../../source/B/BGSEquipSlot.h"
#include "../../../../../../source/B/BGSHeadPart.h"
#include "../../../../../../source/T/TESObjectTREE.h"
#include "../../../../../../source/T/TESFlora.h"
#include "../../../../../../source/T/TESFurniture.h"

namespace PapyrusExtForms
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool RegisterForms(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterObjectType(ConsoleRE::BGSSoundDescriptorForm::TypeID,		"SoundDescriptor");
		VM->RegisterObjectType(ConsoleRE::ActorValueInfo::TypeID,				"ActorValueInfo");
		VM->RegisterObjectType(ConsoleRE::TESObjectARMA::TypeID,				"ArmorAddon");
		VM->RegisterObjectType(ConsoleRE::BGSArtObject::TypeID,					"Art");
		VM->RegisterObjectType(ConsoleRE::BGSColorForm::TypeID,					"ColorForm");
		VM->RegisterObjectType(ConsoleRE::TESCombatStyle::TypeID,				"CombatStyle");
		VM->RegisterObjectType(ConsoleRE::BGSDefaultObjectManager::TypeID,		"DefaultObjectManager");
		VM->RegisterObjectType(ConsoleRE::BGSEquipSlot::TypeID,					"EquipSlot");
		VM->RegisterObjectType(ConsoleRE::BGSHeadPart::TypeID,					"HeadPart");
		VM->RegisterObjectType(ConsoleRE::TESObjectTREE::TypeID,				"TreeObject");
		
		return true;
	}
}