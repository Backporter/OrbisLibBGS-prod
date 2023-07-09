#include "../R/RemoveCallbackVisitor.h"

namespace ConsoleRE
{
	RemoveCallbackVisitor::RemoveCallbackVisitor(void** a_hash) : m_hash(a_hash)
	{}

	void RemoveCallbackVisitor::Process(const GString& a_methodName, FxDelegateHandler::CallbackFn a_method)
	{
		// m_hash->Remove(a_methodName);
	}
}