#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTSmartPointer.h"
#include "../I/IHandlerFunctor.h"

namespace ConsoleRE
{
	template <typename Type, typename Handler, typename Parameter, template <class> class Parent>
	class BSResponse : public Parent<Parameter>, public BSIntrusiveRefCounted
	{
	public:
		using functor_type = IHandlerFunctor<Handler, Parameter>;
	public:
		BSResponse();
		virtual ~BSResponse();
	public:
		BSTHashMap<Type, BSTSmartPointer<functor_type>>               handlerMap;
		BSTSmartPointer<BSResponse<Type, Handler, Parameter, Parent>> backupResponse;
	};
}