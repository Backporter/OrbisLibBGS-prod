#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSAnimationSequencer;

	class ExtraAnimationSequencer : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAnimationSequencer>;
	public:
		~ExtraAnimationSequencer() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BGSAnimationSequencer* sequencer;
	};
	static_assert(sizeof(ExtraAnimationSequencer) == 0x18);
}