#pragma once

#include "../B/BSTSmartPointer.h"
#include "../V/Variable.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IFunction;
		class ObjectTypeInfo;
		class Stack;

		class StackFrame
		{
		public:
			uint32_t		GetOffset() { return parent->GetOffset(this); }
			Variable*		Get(uint32_t a_idx, uint32_t a_unk1) { return parent->Get(this, a_idx, a_unk1); }
		public:
			Stack*							parent;
			StackFrame*						previousFrame;
			BSTSmartPointer<IFunction>      owningFunction;
			BSTSmartPointer<ObjectTypeInfo> owningObjectType;
		};
	}
}