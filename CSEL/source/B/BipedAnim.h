#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../N/NiNode.h"

namespace ConsoleRE
{
	class BipedAnim : public BSIntrusiveRefCounted
	{
	public:
		~BipedAnim();
		void RemoveAllParts();
	public:
		uint32_t Unk04;
		NiNode*  root;
	};
}