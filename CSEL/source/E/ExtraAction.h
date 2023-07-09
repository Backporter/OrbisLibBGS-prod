#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	enum class OBJECT_ACTION
	{
		kNone = 0,
		kUseDefault = 1 << 0,
		kActivate = 1 << 1,
		kOpen = 1 << 2,
		kOpenByDefault = 1 << 3
	};

	class TESObjectREFR;

	class ExtraAction : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAction>;
	public:
		~ExtraAction() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		int8_t									action;
		uint8_t                                 pad11;
		uint16_t                                pad12;
		uint32_t                                pad14;
		TESObjectREFR*                          actionRef;
	};
	static_assert(sizeof(ExtraAction) == 0x20);
}