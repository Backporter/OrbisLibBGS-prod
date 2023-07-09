#pragma once

#include "../G/GFxState.h"
#include "../G/GFxFontMapImpl.h"

namespace ConsoleRE
{
	class GFxFontMap : public GFxState
	{
	public:
		virtual ~GFxFontMap();
	public:
		GFxFontMapImpl* pImpl;
	};
}