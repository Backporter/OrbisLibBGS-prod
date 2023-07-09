#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	// 0x18
	class ExtraHotkey : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHotkey>;

		enum class Hotkey
		{
			kUnbound = static_cast<std::underlying_type_t<Hotkey>>(-1),
			kSlot1 = 0,
			kSlot2 = 1,
			kSlot3 = 2,
			kSlot4 = 3,
			kSlot5 = 4,
			kSlot6 = 5,
			kSlot7 = 6,
			kSlot8 = 7
		};
	public:
		ExtraHotkey();
		explicit ExtraHotkey(int32_t a_hotkey);
		~ExtraHotkey() override = default;

		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint8_t							  hotkey;
		uint8_t                           unk11;
		uint16_t                          unk12;
		uint32_t                          unk14;
	};
	static_assert(sizeof(ExtraHotkey) == 0x18);
}