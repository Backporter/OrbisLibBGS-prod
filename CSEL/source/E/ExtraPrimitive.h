#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSPrimitive;

	class ExtraPrimitive : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPrimitive>;
	public:
		~ExtraPrimitive();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSPrimitive* primitive;
	};
	static_assert(sizeof(ExtraPrimitive) == 0x18);
}