#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class ExtraMagicLight : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMagicLight>;
	public:
		~ExtraMagicLight();

		// override (BSExtraData)
		uint32_t GetType() const override;
	};
	static_assert(sizeof(ExtraMagicLight) == 0x10);
}