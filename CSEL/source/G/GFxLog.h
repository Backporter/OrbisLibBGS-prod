#pragma once

#include "../G/GFxState.h"
#include "../G/GFxLogBase.h"

namespace ConsoleRE
{
	class GFxLog : public GFxState, public GFxLogBase<GFxLog>
	{
	public:
		GFxLog() : GFxState(StateType::State_Log) 
		{}

		~GFxLog() override = default;
		
		// add
		virtual void LogMessageVarg(LogMessageType a_messageType, const char* a_fmt, va_list a_argList)
		{
			va_list args;
			va_copy(args, a_argList);
			va_end(args);
		}
	public:
		void LogMessageByType(LogMessageType a_messageType, const char* a_fmt, ...)
		{
			va_list args;
			va_start(args, a_fmt);
			LogMessageVarg(a_messageType, a_fmt, args);
			va_end(args);
		}
	};
	static_assert(sizeof(GFxLog) == 0x18);
}