#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESTexture : public BaseFormComponent
	{
	public:
		~TESTexture() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add
		virtual uint32_t	GetMaxAllowedSize();
		virtual const char* GetAsNormalFile(BSString&);
		virtual const char* GetDefaultPath();
	public:
		BSFixedString textureName;
	};
	static_assert(sizeof(TESTexture) == 0x10);
}