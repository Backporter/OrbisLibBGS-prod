#pragma once

#include "../N/NiNode.h"

namespace ConsoleRE
{
	class BSNiNode : public NiNode
	{
	public:
		~BSNiNode() override;

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
	public:
	};
	static_assert(sizeof(BSNiNode) == 0x128);
}