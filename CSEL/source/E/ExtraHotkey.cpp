#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraHotkey.h"

namespace ConsoleRE
{
	ExtraHotkey::ExtraHotkey() : ExtraHotkey::ExtraHotkey(std::underlying_type_t<Hotkey>(Hotkey::kUnbound))
	{}

	ExtraHotkey::ExtraHotkey(int32_t a_hotkey) : 
		BSExtraData(), 
		hotkey(a_hotkey), 
		unk11(0),
		unk12(0),
		unk14(0)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraHotkey:.data.rel.ro", 0x1D1CD88);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraHotkey::GetType() const
	{
		return TypeID;
	}

	bool ExtraHotkey::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto s_rhs = static_cast<const ExtraHotkey*>(a_rhs);
		return s_rhs->hotkey != hotkey;
	}
}