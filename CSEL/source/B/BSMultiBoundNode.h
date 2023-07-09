#pragma once

#include "../B/BSCullingProcess.h"
#include "../B/BSNiNode.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSMultiBound;
	class BSMultiBoundRoom;
	class NiPoint3;

	class BSMultiBoundNode : public BSNiNode
	{
	public:
		~BSMultiBoundNode() override;

		// override (BSNiNode)
		const NiRTTI*     GetRTTI() const override;
		BSMultiBoundNode* AsMultiBoundNode() override;
		NiObject*         CreateClone(NiCloningProcess& a_cloning) override;
		void              LoadBinary(NiStream& a_stream) override;
		void              LinkObject(NiStream& a_stream) override;
		bool              RegisterStreamables(NiStream& a_stream) override;
		void              SaveBinary(NiStream& a_stream) override;
		bool              IsEqual(NiObject* a_object) override;
		void              UpdateDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;
		void              UpdateWorldBound() override;
		void              OnVisible(NiCullingProcess& a_process) override;
		void              UpdateUpwardPass(NiUpdateData& a_data) override;

		// add
		virtual BSMultiBoundRoom* GetMultiBoundRoom();
		virtual bool              QPointWithin(const NiPoint3& a_point);
		virtual void              Unk_40(void);
		virtual void              Unk_41(void);
	public:
		NiPointer<BSMultiBound>	multiBound;
		uint32_t				cullingMode;
		float					lastAccumTime;
	};
	static_assert(sizeof(BSMultiBoundNode) == 0x138);
}