#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraCachedScale : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCachedScale>;
	public:
		~ExtraCachedScale() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		float scale3D;
		float refScale;
	};
	static_assert(sizeof(ExtraCachedScale) == 0x18);
}