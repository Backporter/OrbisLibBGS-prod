#pragma once

#include "../F/FxDelegate.h"
#include "../F/FxDelegateHandler.h"

namespace ConsoleRE
{
	class AddCallbackVisitor : public FxDelegateHandler::CallbackProcessor
	{
	public:
		AddCallbackVisitor(FxDelegateHandler* a_handler, void** a_hash);
		virtual ~AddCallbackVisitor() = default;
		
		// override (FxDelegateHandler::CallbackProcessor)
		void Process(const GString& a_methodName, FxDelegateHandler::CallbackFn* a_method) override;
	public:
		FxDelegateHandler*        m_handler;
		void**					  m_hash;
	};
	static_assert(sizeof(AddCallbackVisitor) == 0x18);
}