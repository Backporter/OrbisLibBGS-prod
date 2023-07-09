#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESActorBase;

	class ExtraLeveledCreature : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLeveledCreature>;
	public:
		~ExtraLeveledCreature();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESActorBase* originalBase;
		TESActorBase* templateBase;
	};
	static_assert(sizeof(ExtraLeveledCreature) == 0x20);
}