#pragma once

#include "../B/BaseFormComponent.h"
#include "../T/TESModelRDT.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class TESBipedModelForm : public BaseFormComponent
	{
	public:
		~TESBipedModelForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		TESModelTextureSwap worldModels[2];
		TESModelRDT			constraintTemplate;
	};
	static_assert(sizeof(TESBipedModelForm) == 0xA0);
}