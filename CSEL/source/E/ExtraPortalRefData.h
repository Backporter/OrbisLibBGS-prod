#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct PortalLinkedRefData
	{
		ObjectRefHandle linkedRefs[2];
	};
	static_assert(sizeof(PortalLinkedRefData) == 0x8);

	class ExtraPortalRefData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPortalRefData>;
	public:
		~ExtraPortalRefData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		PortalLinkedRefData* data;
	};
	static_assert(sizeof(ExtraPortalRefData) == 0x18);
}