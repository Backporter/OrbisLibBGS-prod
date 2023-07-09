#pragma once

#include "../N/NiSkinInstance.h"

namespace ConsoleRE
{
	class BSDismemberSkinInstance : public NiSkinInstance
	{
	public:
		struct Data
		{
		public:
			bool          editorVisible;
			bool          startNetBoneSet;
			uint16_t	  slot;
		};
		static_assert(sizeof(Data) == 0x4);
	public:
		~BSDismemberSkinInstance() override;

		// override (NiSkinInstance)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		void          Unk_38() override;
	public:
		int32_t  numPartitions;
		uint32_t Unk74;
		Data*    partitions;
		bool     Unk80;
		uint8_t  Unk81;
		uint16_t Unk82;
		uint32_t Unk84;
	};
	static_assert(sizeof(BSDismemberSkinInstance) == 0x88);
}