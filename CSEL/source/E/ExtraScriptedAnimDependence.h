#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../B/BSTTuple.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraScriptedAnimDependence : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kScriptedAnimDependence>;
	public:
		~ExtraScriptedAnimDependence();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<BSTTuple<ObjectRefHandle, uint32_t>> dependentManagers;
	};
	static_assert(sizeof(ExtraScriptedAnimDependence) == 0x20);
}