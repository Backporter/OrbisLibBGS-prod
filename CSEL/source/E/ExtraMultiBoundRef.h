#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../F/FormTypes.h"

namespace ConsoleRE
{
	class ExtraMultiBoundRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMultiBoundRef>;
	public:
		~ExtraMultiBoundRef();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESObjectREFR* boundRef;
	};
	static_assert(sizeof(ExtraMultiBoundRef) == 0x18);
}