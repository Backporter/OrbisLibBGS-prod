#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraForcedTarget : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kForcedTarget>;
	public:
		~ExtraForcedTarget();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;

		NiPointer<TESObjectREFR> GetTarget();
	public:
		ObjectRefHandle target;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraForcedTarget) == 0x18);
}