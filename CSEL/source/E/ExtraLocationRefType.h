#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSLocationRefType;

	class ExtraLocationRefType : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLocationRefType>;
	public:
		~ExtraLocationRefType();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSLocationRefType* locRefType;
	};
	static_assert(sizeof(ExtraLocationRefType) == 0x18);

}