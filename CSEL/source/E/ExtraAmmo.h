#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAmmo : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAmmo>;
	public:
		~ExtraAmmo() override;

		// override (BSExtraData)
		uint32_t	GetType() const override;
		bool        IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint64_t unk10;
		uint32_t unk18;
		uint32_t pad1C;
	};
	static_assert(sizeof(ExtraAmmo) == 0x20);
}