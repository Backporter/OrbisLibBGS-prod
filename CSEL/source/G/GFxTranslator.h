#pragma once

#include "../G/GFxState.h"

namespace ConsoleRE
{
	class GFxWStringBuffer;

	class GFxTranslator : public GFxState
	{
	public:
		class TranslateInfo
		{
		public:
			enum Flag
			{
				kNone = 0,
				kTranslated = 1 << 0,
				kResultHTML = 1 << 1,
				kResultSourceHTML = 1 << 2
			};
		public:
			TranslateInfo() :key(nullptr), result(nullptr), instanceName(nullptr), flags(Flag::kNone)
			{
			}
		public:
			const wchar_t_t*	key;
			GFxWStringBuffer*   result;
			const char*         instanceName;
			uint8_t				flags;
		};
	public:
		GFxTranslator() : GFxState(StateType::State_Translator), wwMode(0) { }
		GFxTranslator(uint32_t a_mode) : GFxState(StateType::State_Translator), wwMode(a_mode) { }
		~GFxTranslator() override = default;

		virtual uint32_t	GetCaps();
		virtual void		Translate(TranslateInfo*);
		virtual bool		OnWordWrapping(void*);
	public:
		uint32_t wwMode;
	};
}