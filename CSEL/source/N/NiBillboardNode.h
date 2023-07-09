#pragma once

#include "../N/NiNode.h"

namespace ConsoleRE
{
	// 0x130
	class NiBillboardNode : public NiNode
	{
	public:
		~NiBillboardNode() override;
	
		// override (NiNode)
		const NiRTTI*   				GetRTTI() const override;
	public:
		uint16_t	Unk128;
		uint16_t	Unk12A;
		float		Unk12C;
	};
	static_assert(sizeof(NiBillboardNode) == 0x130);
}