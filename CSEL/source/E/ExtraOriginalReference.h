#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraOriginalReference : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOriginalReference>;
	public:
		~ExtraOriginalReference();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		ObjectRefHandle reference;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraOriginalReference) == 0x18);
}