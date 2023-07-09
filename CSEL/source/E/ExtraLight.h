#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiLight;

	struct REFR_LIGHT
	{
		NiPointer<NiLight> light;
		float              wantDimmer;
		uint32_t		   pad0C;
	};
	static_assert(sizeof(REFR_LIGHT) == 0x10);

	class ExtraLight : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLight>;
	public:
		~ExtraLight();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		REFR_LIGHT* lightData;
	};
	static_assert(sizeof(ExtraLight) == 0x18);
}