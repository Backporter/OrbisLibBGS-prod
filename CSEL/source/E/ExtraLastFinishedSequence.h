#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraLastFinishedSequence : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLastFinishedSequence>;
	public:
		~ExtraLastFinishedSequence();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSFixedString lastSequenceName;
	};
	static_assert(sizeof(ExtraLastFinishedSequence) == 0x18);
}