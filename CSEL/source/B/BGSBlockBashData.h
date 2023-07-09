#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSImpactDataSet;
	class BGSMaterialType;

	class BGSBlockBashData : public BaseFormComponent
	{
	public:
		~BGSBlockBashData() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		BGSImpactDataSet* blockBashImpactDataSet;
		BGSMaterialType*  altBlockMaterialType;
	};
	static_assert(sizeof(BGSBlockBashData) == 0x18);
}