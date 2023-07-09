#pragma once

#include "../B/BSFixedString.h"
#include "../N/NiBound.h"
#include "../N/NiObjectNET.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiTransform.h"

namespace ConsoleRE
{
	class NiAlphaProperty;
	class NiAVObject;
	class NiCollisionObject;
	class NiColor;
	class NiColorA;
	class NiCullingProcess;
	class NiNode;
	class NiPoint3;
	class TESObjectREFR;

	struct NiUpdateData
	{
	public:
		NiUpdateData() { }
		NiUpdateData(float a_time, uint32_t a_flags) : m_time(a_time), m_flags(a_flags) { }
	public:
		float	 m_time{ 0 };
		uint32_t m_flags{ 0 };
	};
	static_assert(sizeof(NiUpdateData) == 0x8);

	class PerformOpFunc
	{
	public:
		virtual ~PerformOpFunc();

		// add
		virtual bool Unk_02(NiAVObject* a_object);
	public:
	};
	static_assert(sizeof(PerformOpFunc) == 0x8);

	class NiAVObject : public NiObjectNET
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kHidden = 1 << 0,
			kSelectiveUpdate = 1 << 1,
			kSelectiveUpdateTransforms = 1 << 2,
			kSelectiveUpdateController = 1 << 3,
			kSelectiveUpdateRigid = 1 << 4,
			kDisplayObject = 1 << 5,
			kDisableSorting = 1 << 6,
			kSelectiveUpdateTransformsOverride = 1 << 7,
			kSaveExternalGeometryData = 1 << 9,
			kNoDecals = 1 << 10,
			kAlwaysDraw = 1 << 11,
			kMeshLOD = 1 << 12,
			kFixedBound = 1 << 13,
			kTopFadeNode = 1 << 14,
			kIgnoreFade = 1 << 15,
			kNoAnimSyncX = 1 << 16,
			kNoAnimSyncY = 1 << 17,
			kNoAnimSyncZ = 1 << 18,
			kNoAnimSyncS = 1 << 19,
			kNoDismember = 1 << 20,
			kNoDismemberValidity = 1 << 21,
			kRenderUse = 1 << 22,
			kMaterialsApplied = 1 << 23,
			kHighDetail = 1 << 24,
			kForceUpdate = 1 << 25,
			kPreProcessedNode = 1 << 26
		};
	public:
		~NiAVObject() override;

		// override (NiObjectNET)
		const NiRTTI* GetRTTI() const override;
		void LoadBinary(NiStream& a_stream) override;
		void LinkObject(NiStream& a_stream) override;
		bool RegisterStreamables(NiStream& a_stream) override;
		void SaveBinary(NiStream& a_stream) override;
		bool IsEqual(NiObject* a_object) override;
		void ProcessClone(NiCloningProcess& a_cloning) override;

		// add
		virtual void UpdateControllers(NiUpdateData& a_data);
		virtual void PerformOp(PerformOpFunc& a_func); 
		virtual void AttachProperty(NiAlphaProperty* a_property);
		virtual void SetMaterialNeedsUpdate(bool a_needsUpdate);
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool a_flag);
		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name);
		virtual void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid);
		virtual void UpdateDownwardPass(NiUpdateData& a_data, uint32_t a_arg2);
		virtual void UpdateSelectedDownwardPass(NiUpdateData& a_data, uint32_t a_arg2);
		virtual void UpdateRigidDownwardPass(NiUpdateData& a_data, uint32_t a_arg2);
		virtual void UpdateWorldBound();
		virtual void UpdateWorldData(NiUpdateData* a_data);
		virtual void UpdateTransformAndBounds(NiUpdateData& a_data);
		virtual void PreAttachUpdate(NiNode* a_parent, NiUpdateData& a_data);
		virtual void PostAttachUpdate();
		virtual void OnVisible(NiCullingProcess& a_process);

		//
		void     Update(NiUpdateData& a_data);
		uint32_t UpdateBodyTint(const NiColor& a_color);
		uint32_t UpdateHairColor(const NiColor& a_color);
	public:
		NiNode*							parent;
		uint32_t						parentIndex;
		uint32_t						unk03C;
		NiPointer<NiCollisionObject>	collisionObject;
		NiTransform						local;
		NiTransform						world;
		NiTransform						previousWorld;
		NiBound							worldBound;
		uint32_t						flags;
		TESObjectREFR*					userData;
		float							fadeAmount;
		uint32_t						lastUpdatedFrameCounter;
		uint64_t						unk108;
	};
	static_assert(sizeof(NiAVObject) == 0x110);
}