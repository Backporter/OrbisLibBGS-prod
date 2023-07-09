#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraRefractionProperty : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRefractionProperty>;
	public:
		~ExtraRefractionProperty();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		float    refractionPower;
		uint32_t unk14;
	};
	static_assert(sizeof(ExtraRefractionProperty) == 0x18);
}