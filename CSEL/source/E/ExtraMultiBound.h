#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSMultiBound;

	class ExtraMultiBound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMultiBound>;
	public:
		~ExtraMultiBound();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<BSMultiBound> bound;
	};
	static_assert(sizeof(ExtraMultiBound) == 0x18);
}