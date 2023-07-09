#pragma once

#include "../G/GFxLogConstants.h"

namespace ConsoleRE
{
	template <typename T>
	class GFxLogBase : public GFxLogConstants
	{
	public:
		virtual ~GFxLogBase() { }
		virtual bool IsVerboseActionErrors() { return true; }
	};
}