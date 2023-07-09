#pragma once

#include "../N/NiAVObject.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiTArray.h"

namespace ConsoleRE
{
	class NiNode : public NiAVObject
	{
	public:
		~NiNode() override;

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;
		NiNode*       AsNode() override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		void          ProcessClone(NiCloningProcess& a_cloning) override;
		void          UpdateControllers(NiUpdateData& a_data) override;
		void          PerformOp(PerformOpFunc& a_func) override;
		void          AttachProperty(NiAlphaProperty* a_property) override;
		NiAVObject*   GetObjectByName(const BSFixedString& a_name) override;
		void          SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;
		void          UpdateDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;
		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;
		void          UpdateRigidDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;
		void          UpdateWorldBound() override;
		void          UpdateTransformAndBounds(NiUpdateData& a_data) override;
		void          OnVisible(NiCullingProcess& a_process) override;

		// add
		virtual void AttachChild(NiAVObject* a_child, bool a_firstAvail = false);
		virtual void InsertChildAt(uint32_t a_idx, NiAVObject* a_child);
		virtual void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);
		virtual void DetachChild2(NiAVObject* a_child);
		virtual void DetachChildAt1(uint32_t a_idx, NiPointer<NiAVObject>& a_childOut);
		virtual void DetachChildAt2(uint32_t a_idx);
		virtual void SetAt1(uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);
		virtual void SetAt2(uint32_t a_idx, NiAVObject* a_child);
		virtual void UpdateUpwardPass(NiUpdateData& a_data);
		
		//
		static NiNode* Create(uint16_t a_arrBufLen = 0);
	protected:
		void Ctor(uint16_t a_arrBuffLen);
	public:
		NiTObjectArray<NiPointer<NiAVObject>> children;
	};
	static_assert(sizeof(NiNode) == 0x128);
}