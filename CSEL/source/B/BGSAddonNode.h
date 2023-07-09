#pragma once
#include "../T/TESBoundObject.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class BGSAddonNode :
		public TESBoundObject,
		public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 94;
		BGSAddonNode();
		virtual ~BGSAddonNode();
	public:
	};
}