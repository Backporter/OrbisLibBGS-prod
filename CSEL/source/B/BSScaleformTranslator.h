#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"
#include "../G/GFxTranslator.h"

namespace ConsoleRE
{
	struct BSTranslator
	{
	public:
		BSTHashMap<wchar_t_t*, wchar_t_t*> translationMap;
	};
	static_assert(sizeof(BSTranslator) == 0x20);

	class BSScaleformTranslator : public GFxTranslator
	{
	public:
		~BSScaleformTranslator() override;
		
		// override
		void Translate(TranslateInfo* a_translateInfo) override;
	public:
		BSTranslator translator;
	};
	static_assert(offsetof(BSScaleformTranslator, translator) == 0x18);
	static_assert(sizeof(BSScaleformTranslator) == 0x38);
}