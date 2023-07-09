#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraHealthPerc : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHealthPerc>;
	public:
		~ExtraHealthPerc();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint32_t unk10;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraHealthPerc) == 0x18);
}