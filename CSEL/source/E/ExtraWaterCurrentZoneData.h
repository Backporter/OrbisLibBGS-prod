#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTHashMap.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	namespace BSCurrent
	{
		struct Action;
	}

	class TESObjectCELL;

	class ExtraWaterCurrentZoneData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWaterCurrentZoneData>;
	public:
		~ExtraWaterCurrentZoneData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTHashMap<ObjectRefHandle, BSCurrent::Action*> referenceToActionMap;
		BSCurrent::Action*                              cellAction;
		TESObjectCELL*                                  affectedCell;
		NiPoint3                                        angularVelocity;
		NiPoint3                                        linearVelocity;
	};
	static_assert(sizeof(ExtraWaterCurrentZoneData) == 0x58);
}