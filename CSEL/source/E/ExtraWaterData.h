#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../H/hkRefPtr.h"

namespace ConsoleRE
{
	class ExtraWaterData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWaterData>;
	public:
		~ExtraWaterData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		uint64_t					 unk10;
		hkRefPtr<hkReferencedObject> unk18;
		void*						 currentArray;
	};
	static_assert(sizeof(ExtraWaterData) == 0x28);
}