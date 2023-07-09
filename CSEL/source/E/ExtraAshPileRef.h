#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAshPileRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAshPileRef>;
	public:
		ExtraAshPileRef();
		explicit ExtraAshPileRef(uint32_t a_ashPileRef);
		~ExtraAshPileRef() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t ashPileRef;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraAshPileRef) == 0x18);
}
