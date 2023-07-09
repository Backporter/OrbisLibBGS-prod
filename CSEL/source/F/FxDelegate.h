#pragma once

#include "../F/FxDelegateHandler.h"
#include "../G/GFxExternalInterface.h"
// #include "../G/GHash.h"
#include "../G/GPtr.h"
#include "../G/GString.h"

namespace ConsoleRE
{
	class FxResponseArgsBase;
	class GFxMovieView;

	class FxDelegate : public GFxExternalInterface
	{
	public:
		struct CallbackDefn
		{
		public:
			GPtr<FxDelegateHandler>        handler{ nullptr };
			FxDelegateHandler::CallbackFn* callback{ nullptr };
		};
		static_assert(sizeof(CallbackDefn) == 0x10);

		struct CallbackHashFunctor
		{
			size_t operator()(const GString& a_data) const
			{
				return GString::BernsteinHashFunction(a_data.c_str(), a_data.length());
			}
		};
	public:
		FxDelegate() = default;
		~FxDelegate() override = default;

		// override (GFxExternalInterface)
		void Callback(GFxMovieView* a_movieView, const char* a_methodName, const GFxValue* a_args, uint32_t a_argCount) override;

		static void Invoke(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args);
		static void Invoke2(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args);
		
		void RegisterHandler(FxDelegateHandler* a_callback);
		void UnregisterHandler(FxDelegateHandler* a_callback);
	public:
		void* callbacks;
	};
	static_assert(sizeof(FxDelegate) == 0x18);
}