#pragma once
#include "../B/BSFaceGenKeyframe.h"

namespace ConsoleRE
{
	class BSFaceGenKeyframeMultiple : public BSFaceGenKeyframe
	{
	public:
		BSFaceGenKeyframeMultiple();
		virtual ~BSFaceGenKeyframeMultiple();
	public:
		float*	 Unk10;
		uint32_t Unk18;
		bool	 Unk1C;
		bool	 Unk1D;
		bool	 Unk1E;
		bool	 Unk1F;
	};
	static_assert(sizeof(BSFaceGenKeyframeMultiple) == 0x20, "");
}