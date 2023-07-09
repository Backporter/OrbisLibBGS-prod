#pragma once

#include "../B/BSAtomic.h"
#include "../N/NiObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiAVObject;
	class NiTransform;
	class NiSkinData;
	class NiSkinPartition;

	class NiSkinInstance : public NiObject
	{
	public:
		~NiSkinInstance() override;

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		void          PostLinkObject(NiStream& a_stream) override;

		// add
		virtual void Unk_38(); 

		static NiSkinInstance* Create();
	public:
		NiPointer<NiSkinData>      skinData;
		NiPointer<NiSkinPartition> skinPartition;
		NiAVObject*                rootParent;
		NiAVObject**               bones;
		const NiTransform**        boneWorldTransforms;
		uint32_t				   frameID;
		uint32_t				   numMatrices;
		uint32_t				   numRegisters;
		uint32_t				   allocatedSize;
		void*                      boneMatrices;
		void*                      prevBoneMatrices;
		void*                      skinToWorldWorldToSkinMatrix;
		BSCriticalSection		   lock;
		void*					   Unk68;
	};
	static_assert(sizeof(NiSkinInstance) == 0x70);
}