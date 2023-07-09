#pragma once

#include "../B/BSIntrusiveRefCounted.h"

#include <stdint.h>

namespace ConsoleRE
{
	template <class T, class D>
	class IHandlerFunctor : public BSIntrusiveRefCounted
	{
	public:
		virtual ~IHandlerFunctor() = default;

		// add
		virtual bool ExecuteHandler(T*, const D&) = 0;
	public:
		uint32_t pad0C;
	};
}