#pragma once

#include "../G/GFxState.h"

namespace ConsoleRE
{
	class GFxMovieView;
	class GFxValue;

	class GFxExternalInterface : public GFxState
	{
	public:
		GFxExternalInterface() : GFxState(StateType::State_ExternalInterface) { }
		~GFxExternalInterface() override = default;

		// add
		virtual void Callback(GFxMovieView* a_movieView, const char* a_methodName, const GFxValue* a_args, uint32_t a_numArgs) = 0;
	public:
	};
	static_assert(sizeof(GFxExternalInterface) == 0x10);
}