#pragma once

#include "../F/FormTypes.h"
#include "../T/TESBoundObject.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class BGSMaterialObject;

	struct TESObjectSTATData
	{
	public:
		float                            materialThresholdAngle;
		uint32_t						 pad04;
		BGSMaterialObject*               materialObj;
		uint32_t						 flags;
		uint32_t                         pad14;
	};
	static_assert(sizeof(TESObjectSTATData) == 0x18);

	class TESObjectSTAT : public TESBoundObject, public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 34;
		
		~TESObjectSTAT() override;
		
		// override (TESBoundObject)
		void               ClearData() override;
		bool               Load(TESFile* a_mod) override;
		void               InitItemImpl() override;
		bool               GetPlayable() const override;
		bool			   IsHeadingMarker() const override;
	public:
		TESObjectSTATData data;
	};
	static_assert(sizeof(TESObjectSTAT) == 0x78);
}