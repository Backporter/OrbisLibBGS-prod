#pragma once

#include "../B/BSFixedString.h"
#include "../N/NiColor.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSMaterialType : public TESForm
	{
	public:
		static constexpr int TypeID = 99;
	public:
		~BGSMaterialType() override;
		
		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BGSMaterialType*                      parentType;
		BSFixedString                         materialName;
		uint32_t							  materialID;
		NiColor                               materialColor;
		float                                 buoyancy;
		uint32_t							  flags;
		BGSImpactDataSet*                     havokImpactDataSet;
	};
	static_assert(sizeof(BGSMaterialType) == 0x50);
}