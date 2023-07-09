#include "../N/NiNode.h"

namespace ConsoleRE
{
	NiNode* NiNode::Create(uint16_t a_arrBufLen)
	{
		NiNode* node = (NiNode*)malloc(sizeof(NiNode));
		memset((void*)node, 0, sizeof(NiNode));
		node->Ctor(a_arrBufLen);
		return node;
	}

	void NiNode::Ctor(uint16_t a_arrBuffLen)
	{
		using func_t = decltype(&NiNode::Ctor);
		Relocation<func_t> func("", 0xE89700);
		return func(this, a_arrBuffLen);
	}
}