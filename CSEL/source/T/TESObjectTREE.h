#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTArray.h"
#include "../F/FormTypes.h"
#include "../N/NiMatrix3.h"
#include "../N/NiPoint3.h"
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModel.h"
#include "../T/TESProduceForm.h"

namespace ConsoleRE
{
	struct OBJ_TREE
	{
		float trunkFlexibility;
		float branchFlexibility;
		float trunkAmplitude;
		float frontAmplitude;
		float backAmplitude;
		float sideAmplitude;
		float frontFrequency;
		float backFrequency;
		float sideFrequency;
		float leafFlexibility;
		float leafAmplitude;
		float leafFrequency;
	};
	static_assert(sizeof(OBJ_TREE) == 0x30);

	struct BoneData
	{
		NiMatrix3		localBoneRotation;
		NiPoint3		worldBoneDir;
		uint32_t		parentWorldBoneRotationIndex;
	};
	static_assert(sizeof(BoneData) == 0x34);

	struct BaseTreeData : public BSIntrusiveRefCounted
	{
		uint32_t			pad04;
		BSTArray<BoneData>  branchBoneData;
		BSTArray<NiMatrix3> parentWorldBoneRotations;
	};
	static_assert(sizeof(BaseTreeData) == 0x28);

	class TESObjectTREE : public TESBoundObject, public TESModel, public TESFullName, public TESProduceForm
	{
	public:
		static constexpr int TypeID = 38;
	public:
		~TESObjectTREE() override;
	
		// override (TESBoundObject)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		bool ReplaceModel() override;
		bool GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		void OnRemove3D(NiAVObject* a_obj3D) override;
		void OnCheckModels() override;
		void OnCopyReference() override;
		void OnFinishScale() override;
	public:
		OBJ_TREE		data;
		BaseTreeData*	baseData;
		uint32_t		type;
	};
	static_assert(sizeof(TESObjectTREE) == 0xC0);

}