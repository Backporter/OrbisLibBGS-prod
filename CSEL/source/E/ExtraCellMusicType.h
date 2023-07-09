#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSMusicType;

	class ExtraCellMusicType : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCellMusicType>;
	public:
		~ExtraCellMusicType();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSMusicType* type;
	};
	static_assert(sizeof(ExtraCellMusicType) == 0x18);
}