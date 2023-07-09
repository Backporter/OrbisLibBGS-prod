#pragma once

#include "../N/NiNode.h"

namespace ConsoleRE
{
	class BSLeafAnimNode;
	class BSTreeNode;

	class BSFadeNode : public NiNode
	{
	public:
		~BSFadeNode() override;

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;
		BSFadeNode*   AsFadeNode() override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;
		void          OnVisible(NiCullingProcess& a_process) override;

		// add
		virtual BSTreeNode*     AsTreeNode();
		virtual BSLeafAnimNode* AsLeafAnimNode();
	public:
		float    unk128;
		float    unk12C;
		float    currentFade;
		uint32_t unk134;
		uint32_t unk138;
		uint32_t unk13C;
		float    unk140;
		uint32_t unk144;
		uint32_t unk148;
		float    unk14C;
		uint16_t unk150;
		uint8_t  unk152;
		uint8_t  unk153;
		uint8_t  unk154;
		uint8_t  unk155;
		uint16_t unk156;
	};
	static_assert(sizeof(BSFadeNode) == 0x158);
}