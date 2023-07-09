#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAlphaCutoff : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAlphaCutoff>;
	public:
		~ExtraAlphaCutoff() override;

		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool        IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		int8_t   cutoff;
		int8_t   originalCutoff;
		uint16_t pad12;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraAlphaCutoff) == 0x18);
}