#pragma once

#include "../B/BSAtomic.h"

#include "../B/BSTHashMap.h"
#include "../E/ExtraDataList.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiPoint3.h"

#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	class TESObjectREFR;
	class TESObjectLAND;
	class TESWorldSpace;

	class TESObjectCELL : public TESForm, public TESFullName
	{
	public:
		static constexpr int TypeID = 60;
	public:
		~TESObjectCELL() override;
		
		//
		bool IsExteriorCell()  { return !IsInteriorCell(); }
		bool IsInteriorCell()  { return (cellFlags & 1) == 1; }
		bool UsesSkyLighting() { return (cellFlags & 256) == 256; }
	public:
		mutable BSSpinLock                        grassCreateLock;
		mutable BSSpinLock                        grassTaskLock;
		uint16_t								  cellFlags;
		uint16_t								  cellGameFlags;
		uint8_t									  cellState;
		bool									  autoWaterLoaded;
		bool                                      cellDetached;
		uint8_t                                   Unk57;
		ExtraDataList							  extraList;
		void*									  cellData;
		TESObjectLAND*							  cellLand;
		float									  waterHeight;
		uint32_t								  Unk8C;
		void*									  Unk90;
		BSTHashMap<UnkKey, UnkValue>			  Unk98; // 
		TESForm*								  UnkB8;
		BSTArray<TESObjectREFR*>				  objectList;
		BSTArray<void*>							  UnkD0;
		BSTArray<void*>							  UnkE0;
		BSTArray<void*>							  UnkF0;
		mutable BSSpinLock                        spinLock;
		TESWorldSpace*							  worldSpace;
		void*									  loadedData;
		void*									  lightingTemplate;
		void*									  Unk128;
	};
	static_assert(sizeof(TESObjectCELL) == 0x130);
}