#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSOcclusionShape;

	class ExtraOcclusionShape : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOcclusionShape>;
	public:
		~ExtraOcclusionShape();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<BSOcclusionShape> shape;
	};
	static_assert(sizeof(ExtraOcclusionShape) == 0x18);
}