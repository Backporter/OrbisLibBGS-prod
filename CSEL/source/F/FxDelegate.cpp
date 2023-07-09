#include "../F/FxDelegate.h"

#include "../F/FxDelegateArgs.h"
#include "../F/FxResponseArgsBase.h"
#include "../G/GFxMovieView.h"
#include "../G/GFxValue.h"
#include "../A/AddCallbackVisitor.h"
#include "../R/RemoveCallbackVisitor.h"

namespace ConsoleRE
{
	void FxDelegate::Invoke(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args)
	{
		assert(a_movieView);
		GFxValue* values = nullptr;
		const uint32_t numValues = a_args.GetValues(&values);
		if (values)
		{
			values[0] = a_methodName;
			a_movieView->InvokeNoReturn((char*)"call", values, numValues);
		}
	}

	void FxDelegate::Invoke2(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args)
	{
		assert(a_movieView);
		GFxValue* values = nullptr;
		const uint32_t numValues = a_args.GetValues(&values);
		if (values)
		{
			a_movieView->Invoke(a_methodName, nullptr, values + 1, numValues - 1);
		}
	}

	void FxDelegate::RegisterHandler(FxDelegateHandler* a_callback)
	{
		assert(a_callback);
		AddCallbackVisitor reg(a_callback, &callbacks);
		a_callback->Accept(&reg);
	}

	void FxDelegate::UnregisterHandler(FxDelegateHandler* a_callback)
	{
		assert(a_callback);
		RemoveCallbackVisitor reg(&callbacks);
		a_callback->Accept(&reg);
	}
}