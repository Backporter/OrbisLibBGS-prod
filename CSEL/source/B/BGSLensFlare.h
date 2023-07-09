#pragma once

#include "../B/BSLensFlareRenderData.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSLensFlare :
		public TESForm,
		public BSLensFlareRenderData
	{
	public:
		static constexpr int TypeID = 135;
	public:
	};
}