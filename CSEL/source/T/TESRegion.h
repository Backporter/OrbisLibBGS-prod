#pragma once

#include "../B/BSTList.h"
#include "../F/FormTypes.h"
#include "../N/NiColor.h"
#include "../N/NiPoint2.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class TESRegionData;

	struct TESRegionDataList
	{
		BSSimpleList<TESRegionData*> regionDataList;
		bool                         unk11;
		uint16_t					 pad12;
		uint32_t					 pad14;
	};
	static_assert(sizeof(TESRegionDataList) == 0x18);

	class TESRegionPoint
	{
	public:
		NiPoint2 point;
	};
	static_assert(sizeof(TESRegionPoint) == 0x8);

	class TESRegionPointList : public BSSimpleList<TESRegionPoint*>
	{
	public:
		struct ScaleResult
		{
			TESRegionPoint point;
			float          dist;
			float          scale;
		};
		static_assert(sizeof(ScaleResult) == 0x10);

		ScaleResult*	lastScaleResult;
		bool			ownsPointMemory;
		uint8_t			pad19;
		uint16_t		pad1A;
		NiPoint2		minimums;
		NiPoint2		maximums;
		uint32_t		distanceInsideAtMax;
		uint32_t		count;
		uint32_t		pad34;
	};
	static_assert(sizeof(TESRegionPointList) == 0x38);

	class TESRegion : public TESForm
	{
	public:
		static constexpr int TypeID = 58;
	public:
		~TESRegion() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;

		// add
		virtual bool Validate();
	public:
		TESRegionDataList*                 dataList;
		BSSimpleList<TESRegionPointList*>* pointLists;
		TESWorldSpace*                     worldSpace;
		TESWeather*                        currentWeather;
		NiColor                            emittanceColor;
		uint32_t						   pad4C;
	};
	static_assert(sizeof(TESRegion) == 0x50);
}