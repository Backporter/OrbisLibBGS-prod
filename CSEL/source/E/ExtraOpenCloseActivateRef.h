#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraOpenCloseActivateRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOpenCloseActivateRef>;
	public:
		~ExtraOpenCloseActivateRef();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		ObjectRefHandle activateRef;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraOpenCloseActivateRef) == 0x18);
}