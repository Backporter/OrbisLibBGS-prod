#pragma once
#include "../N/NiNode.h"

namespace ConsoleRE
{
	class BSFaceGenNiNode : public NiNode
	{
	public:
		virtual ~BSFaceGenNiNode();
	public:
		void UpdateModelFace()
		{
			using func_t = void(decltype(this));
			Relocation<func_t*> func("", 0x4817C0);
			return func(this);
		}

		void AdjustHeadMorph(uint32_t a_unk2, uint32_t a_unk3, float a_unk4)
		{
			using func_t = void(decltype(this), uint32_t, uint32_t, float);
			Relocation<func_t*> func("", 0x0);
			return func(this, a_unk2, a_unk3, a_unk4);
		}
	};
}