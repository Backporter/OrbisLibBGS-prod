#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class ExtraGroupConstraint : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kGroupConstraint>;
	public:
		~ExtraGroupConstraint();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		int32_t    		constraintType;
		ObjectRefHandle entityB;
		BSFixedString   attachNodeNameA;
		BSFixedString   attachNodeNameB;
		NiPoint3        constraintOffsetA;
		NiPoint3        constraintOffsetB;
		uint32_t		originalCollisionGroupB;
		float           dynamicMassScaleB;
	};
	static_assert(sizeof(ExtraGroupConstraint) == 0x48);
}