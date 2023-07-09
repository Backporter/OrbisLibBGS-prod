#pragma once

#include "../G/GRefCountBase.h"

namespace ConsoleRE
{
	class GFxValue;
	class GFxMovie;

	class GFxFunctionHandler : public GRefCountBase<GFxFunctionHandler, 2>
	{
	public:
		struct Params
		{
			GFxValue* const retVal;
			GFxMovie* const movie;
			GFxValue* const thisPtr;
			GFxValue* const argsWithThisRef;
			GFxValue* const args;
			const uint32_t	argCount;
			void* const		userData;
		};
		static_assert(sizeof(Params) == 0x38);
	public:
		virtual ~GFxFunctionHandler() = default;
		
		// add
		virtual void Call(Params& a_params) = 0;
	};
	static_assert(sizeof(GFxFunctionHandler) == 0x10);
}