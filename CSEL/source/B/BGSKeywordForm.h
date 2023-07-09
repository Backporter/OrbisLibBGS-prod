#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSKeyword;

	class BGSKeywordForm : public BaseFormComponent
	{
	public:
		~BGSKeywordForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add (BGSKeywordForm)
		virtual bool		HasKeyword(const BGSKeyword*) const;
		virtual BGSKeyword* GetDefaultKeyword() const;
	public:
		BGSKeyword** keywords;
		uint32_t	 numKeywords;
	};
	static_assert(sizeof(BGSKeywordForm) == 0x18);
}