#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESForm;
	class TESModel;

	class ExtraModelSwap : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kModelSwap>;
	public:
		~ExtraModelSwap();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESModel* modelSwap;
		TESForm*  modelSwapForm;
	};
	static_assert(sizeof(ExtraModelSwap) == 0x20);
}