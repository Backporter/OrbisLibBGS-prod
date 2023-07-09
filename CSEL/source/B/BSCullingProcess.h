#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTLocklessQueue.h"
#include "../N/NiCullingProcess.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSCompoundFrustum;
	class BSMultiBound;
	class BSOcclusionPlane;
	class NiAVObject;
	class NiBound;

	class BSCullingProcess : public NiCullingProcess
	{
	public:
		struct Data
		{
		public:
			uint8_t unk00[0x10];
		};
		static_assert(sizeof(Data) == 0x10);
	public:
		// override (NiCullingProcess)
		const NiRTTI* GetRTTI() const override;

		~BSCullingProcess() override;
		
		// override (NiCullingProcess)
		void Process1(NiAVObject* a_object, uint32_t a_arg2) override;
		void Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet) override;
		void AppendVirtual(BSGeometry& a_visible, uint32_t a_arg2) override;
	public:
		BSTArray<NiPointer<NiAVObject>>                   unk00128;
		BSTLocklessQueue::ObjMultiProdCons<Data, 4096, 0> cullQueue;
		
		// NEEDS RE, [Expected Size - Current size(minus this entry)]
		uint8_t	UNK[0x30600 - 0x30158];
	};
	static_assert(sizeof(BSCullingProcess) == 0x30600);
}