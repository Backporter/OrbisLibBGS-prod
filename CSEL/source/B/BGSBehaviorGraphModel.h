#pragma once

#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSBehaviorGraphModel : public TESModel
	{
	public:
		~BGSBehaviorGraphModel() override;

		// override (TESModel)
		void SetModel(const char* a_model) override;
	};
	static_assert(sizeof(BGSBehaviorGraphModel) == 0x28);

}