#pragma once

#include "../G/GRefCountBase.h"

namespace ConsoleRE
{
	class FxDelegateArgs;
	class GString;

	class FxDelegateHandler : public GRefCountBase<FxDelegateHandler, 2>
	{
	public:
		using CallbackFn = void(const FxDelegateArgs&);

		class CallbackProcessor
		{
		public:
			virtual ~CallbackProcessor() = default;
			
			// add
			virtual void Process(const GString&, CallbackFn*) = 0;
		};
		static_assert(sizeof(CallbackProcessor) == 0x8);
	public:
		~FxDelegateHandler() override = default;

		// add
		virtual void Accept(CallbackProcessor*) = 0;
	};
	static_assert(sizeof(FxDelegateHandler) == 0x10);
}