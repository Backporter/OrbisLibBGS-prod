#pragma once

#include "../B/BSFixedString.h"
#include "../E/ErrorLogger.h"

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class Logger : public BSScript::ErrorLogger
		{
		public:
			~Logger() override;

			// override (BSScript::ErrorLogger)
			void PostErrorImpl(const char* LogEvent, uint32_t Severity) override;
		public:
			BSFixedString logName;
			BSFixedString logPath;
			void*		  Unk98;
		};
		static_assert(sizeof(Logger) == 0x98);
	}
}