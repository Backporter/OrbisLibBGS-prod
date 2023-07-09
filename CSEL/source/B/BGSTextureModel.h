#pragma once

#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSTextureModel : public TESModel
	{
	public:
		virtual ~BGSTextureModel();

		// override (TESModel)
		void SetModel(const char* a_model) override;
	};
	static_assert(sizeof(BGSTextureModel) == 0x28);
}