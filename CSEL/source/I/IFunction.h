#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal { class VirtualMachine; }
		
		class TypeInfo;
		class Stack;
		class StackFrame;
		class ErrorLogger;

		// not exposed inside the ELF(?) so we use PC defs as its unlikely they would change
		class IFunction : public BSIntrusiveRefCounted
		{
		public:
			IFunction() : Unk0C(0) { }
			virtual ~IFunction() = default;

			// add (IFunction)
			virtual const BSFixedString&		GetName() = 0;
			virtual const BSFixedString&		GetObjectTypeName() = 0;
			virtual const BSFixedString&		GetStateName() = 0;
			virtual TypeInfo					GetReturnType() = 0;
			virtual uint32_t					GetParamCount() = 0;
			virtual void						GetParam(uint32_t a_idx, BSFixedString& a_nameOut, TypeInfo& a_typeOut) = 0;
			virtual uint32_t					GetStackFrameSize() = 0;
			virtual bool						GetIsNative() = 0;
			virtual bool						GetIsStatic() = 0;
			virtual bool						GetIsEmpty() = 0;
			virtual uint32_t					GetFunctionType() = 0;
			virtual uint32_t					GetUserFlags() = 0;
			virtual BSFixedString&				GetDocString() = 0;
			virtual void						InsertLocals(StackFrame* a_frame) = 0;
			virtual uint32_t					Call(BSTSmartPointer<Stack>& Stack, ErrorLogger* a_logger, Internal::VirtualMachine* a_vm, bool a_arg4) = 0;
			virtual BSFixedString&				GetSourceFilename(void) = 0;
			virtual bool						TranslateIPToLineNumber(uint32_t a_indexPtr, uint32_t& a_lineNumberOut) = 0;
			virtual bool						GetVarNameForStackIndex(uint32_t a_idx, BSFixedString& a_nameOut) = 0;
			virtual bool						CanBeCalledFromTasklets(void) = 0;
			virtual void						SetCallableFromTasklets(bool a_callable) = 0;
		public:
			uint32_t Unk0C;
		};
	}
}
