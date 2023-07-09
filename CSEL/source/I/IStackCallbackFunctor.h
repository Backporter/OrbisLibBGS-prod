#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IStackCallbackFunctor : public BSIntrusiveRefCounted
		{
		public:
			IStackCallbackFunctor() : pad0C(0) {}
			virtual ~IStackCallbackFunctor() = default;

			virtual void Unk_02() = 0;
			virtual bool Unk_03() { return false; }
			virtual void Unk_04() = 0;
		public:
			uint32_t pad0C;
		};
	}
}