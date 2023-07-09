#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct ExtraLightDataStruct
	{
		ExtraLightDataStruct();
		~ExtraLightDataStruct() = default;

		float         fov;
		float         fade;
		float         endDistanceCap;
		float         shadowDepthBias;
		uint8_t		  unk10;
		uint8_t		  pad11;
		uint16_t	  pad12;
	};
	static_assert(sizeof(ExtraLightDataStruct) == 0x14);

	class ExtraLightData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLightData>;
	public:
		~ExtraLightData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		ExtraLightDataStruct data;
		uint32_t			 pad24;
	};
	static_assert(sizeof(ExtraLightData) == 0x28);
}