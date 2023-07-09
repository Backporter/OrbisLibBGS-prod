#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraHotkey.h"
#include "../I/InventoryChanges.h"

#include <functional>

#include "../Helper.h"

namespace ConsoleRE
{
	class ExtraContainerChanges : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kContainerChanges>;
	public:
		ExtraContainerChanges();
		explicit ExtraContainerChanges(InventoryChanges* a_changes);
		~ExtraContainerChanges() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		template<class Op>
		void FindEquipped(Op& a_op, TESBoundObject*& a_dstForm, ExtraDataList*& a_dstdist, bool isWorn = true, bool isWornLeft = true)
		{
			Helper::EquipmentSlotMatcherT<Op> EquipmentMatcher(a_op, isWorn, isWornLeft);

			if (changes && changes->entryList)
			{
				changes->entryList->Visit(EquipmentMatcher);
			}

			EquipmentMatcher.Get(a_dstForm, a_dstdist);
		}

		void FindHotkey(TESForm*& a_dstForm, ExtraHotkey*& a_dstHotkey, int32_t a_hostkey)
		{
			Helper::HotkeyFinder hotkeyhelper(a_hostkey);

			if (changes && changes->entryList)
			{
				changes->entryList->Visit(hotkeyhelper);
			}

			hotkeyhelper.Get(a_dstForm, a_dstHotkey);
		}

		void FindHotkey(TESForm*& a_dstForm, ExtraHotkey*& a_dstHotkey, TESForm* a_hostkey)
		{
			Helper::HotkeyFinder hotkeyhelper(a_hostkey);

			if (changes && changes->entryList)
			{	
				changes->entryList->Visit(hotkeyhelper);
			}

			hotkeyhelper.Get(a_dstForm, a_dstHotkey);
		}
	public:
		InventoryChanges* changes;
	};
	static_assert(sizeof(ExtraContainerChanges) == 0x18);
}