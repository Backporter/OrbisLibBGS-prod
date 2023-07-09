#pragma once

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		struct ILoader;

		class IObjectProcessor
		{
		public:
			virtual ~IObjectProcessor();

			// add (IObjectProcessor)
			virtual IObjectProcessor*	Clone() = 0;
			virtual void				SetLoader(ILoader* a_loader) = 0;
			virtual bool				Process(const BSFixedString& a_className) = 0;
		};
		static_assert(sizeof(IObjectProcessor) == 0x8);
	}
}