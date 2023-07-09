#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESForm;

	class ExtraEmittanceSource : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEmittanceSource>;
	public:
		~ExtraEmittanceSource();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESForm* source;
	};
}