#include "../A/AddCallbackVisitor.h"

namespace ConsoleRE
{
	AddCallbackVisitor::AddCallbackVisitor(FxDelegateHandler* a_handler, void** a_hash) : 
		m_handler(a_handler), m_hash(a_hash)
	{}

	void AddCallbackVisitor::Process(const GString& a_methodName, FxDelegateHandler::CallbackFn* a_method)
	{
		FxDelegate::CallbackDefn cbDef;
		cbDef.handler.reset(m_handler);
		cbDef.callback = a_method;

		// hash->Add(a_methodName, cbDef);
	}
}