#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraNorthRotation : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kNorthRotation>;
	public:
		~ExtraNorthRotation();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		float    northRot;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraNorthRotation) == 0x18);
}