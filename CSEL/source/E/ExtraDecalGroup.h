#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct BGSDecalGroup;

	class ExtraDecalGroup : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kDecalGroup>;
	public:
		~ExtraDecalGroup();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BGSDecalGroup* decalGroup;
	};
	static_assert(sizeof(ExtraDecalGroup) == 0x18);
}