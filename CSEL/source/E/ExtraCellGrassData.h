#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class AddCellGrassTask;
	class BSInstanceTriShape;

	struct CellGrassData
	{
		uint64_t					  grassTypeKey;
		BSFixedString                 grassModelKey;
		NiPointer<BSInstanceTriShape> triShape;
		BSTArray<void*>               unk18;
		BSTArray<void*>               unk30;
	};
	static_assert(sizeof(CellGrassData) == 0x38);

	class ExtraCellGrassData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCellGrassData>;
	public:
		~ExtraCellGrassData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<CellGrassData*>    grassHandles;
		NiPointer<AddCellGrassTask> addGrassTask;
	};
	static_assert(sizeof(ExtraCellGrassData) == 0x28);
}