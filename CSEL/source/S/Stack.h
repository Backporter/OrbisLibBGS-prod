#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTArray.h"
#include "../B/BSTSmartPointer.h"
#include "../M/MemoryPage.h"
#include "../V/Variable.h"

// 
#include "../C/CodeTasklet.h"

#include "../I/IStackCallbackFunctor.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			class CodeTasklet;
		}

		class IProfilePolicy;
		class IStackCallbackFunctor;
		class StackFrame;
		class Variable;
		struct IMemoryPagePolicy;

		class Stack : public BSIntrusiveRefCounted
		{
		public:
			struct MemoryPageData
			{
			public:
				BSTAutoPointer<MemoryPage>	page;
				uint32_t					availableMemoryInBytes;
				uint32_t					pad0C;
			};
			static_assert(sizeof(MemoryPageData) == 0x10, "");
		public:
			~Stack() 
			{ 
				dtor(); 
			}

			uint32_t GetOffset(StackFrame* const a_frame)
			{
				using func_t = uint32_t(Stack* const, StackFrame* const);
				Relocation<func_t*> func("", 0x155D820);
				return func(this, a_frame);
			}

			Variable* Get(const StackFrame* a_frame, uint32_t a_Index, uint32_t a_offset)
			{
				using func_t = Variable*(Stack* const, const StackFrame*, uint32_t, uint32_t);
				Relocation<func_t*> func("", 0x15608E0);
				return func(this, a_frame, a_Index, a_offset);
			}
		public:
			uint32_t									 pad04;
			IMemoryPagePolicy*                           policy;
			IProfilePolicy*                              profilePolicy;
			BSTSmallArray<MemoryPageData, 3>             pages;
			uint32_t									 frames;
			uint32_t									 pad5C;
			StackFrame*                                  top;
			uint32_t									 state;
			uint32_t									 freezeState;
			Variable                                    returnValue;
			uint32_t									 stackID;
			uint32_t									 stackType;
			BSTSmartPointer<Internal::CodeTasklet>       owningTasklet;
			BSTSmartPointer<IStackCallbackFunctor>       callback;
			BSTSmartPointer<Stack>                       nextStack;
		private:
			void dtor()
			{
				using func_t = void(Stack* const);
				Relocation<func_t*> func("", 0x155FDF0);
				return func(this);
			}
		};
		static_assert(sizeof(Stack) == 0xA0);
	}
}