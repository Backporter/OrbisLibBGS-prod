#pragma once

#include "../F/FxDelegate.h"
#include "../F/FxDelegateHandler.h"

namespace ConsoleRE
{
	class RemoveCallbackVisitor : public FxDelegateHandler::CallbackProcessor
	{
	public:
		RemoveCallbackVisitor(void** a_hash);
		~RemoveCallbackVisitor() override = default;

		// override (FxDelegateHandler::CallbackProcessor)
		void Process(const GString& a_methodName, FxDelegateHandler::CallbackFn a_method) override;
	public:
		void** m_hash;  // 08
	};
	static_assert(sizeof(RemoveCallbackVisitor) == 0x10);
}
