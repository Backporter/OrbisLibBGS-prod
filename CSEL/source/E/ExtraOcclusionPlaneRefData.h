#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct OcclusionPlaneLinkedRefData
	{
		ObjectRefHandle linkedRefs[4];
	};
	static_assert(sizeof(OcclusionPlaneLinkedRefData) == 0x10);

	class ExtraOcclusionPlaneRefData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOcclusionPlaneRefData>;
	public:
		~ExtraOcclusionPlaneRefData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		OcclusionPlaneLinkedRefData* data;
	};
	static_assert(sizeof(ExtraOcclusionPlaneRefData) == 0x18);
}