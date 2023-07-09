#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraReflectorRefs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kReflectorRefs>;
	public:
		~ExtraReflectorRefs();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTArray<ObjectRefHandle> refs;
	};
	static_assert(sizeof(ExtraReflectorRefs) == 0x20);
}