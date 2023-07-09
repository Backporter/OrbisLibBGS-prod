#pragma once

#include "../B/BSTEvent.h"
#include "../B/BSTHashMap.h"
#include "../L/LogEvent.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class ErrorLogger : public BSTEventSource<LogEvent>
		{
		public:
			enum Severity : uint32_t
			{
				Info,
				Warning,
				Error,
				Fatal,
				Invalid
			};

			virtual ~ErrorLogger();

			// add
			virtual void PostErrorImpl(const char* LogEvent, uint32_t Severity) = 0;
			virtual void ResetImpl();
		private:
			mutable BSSpinLock								threadErrorsLock;
			BSTHashMap<uint32_t, uint32_t>					threadErrors;
		};
		static_assert(sizeof(ErrorLogger) == 0x80);
	}
}