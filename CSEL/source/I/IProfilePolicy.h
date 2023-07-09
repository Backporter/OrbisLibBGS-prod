#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			class IFuncCallQuery;;
		}
		
		class Variable;

		class IProfilePolicy
		{
		public:
			virtual ~IProfilePolicy();

			// add
			virtual void StackFramePushQueued(uint32_t, uint32_t, const BSTSmartPointer<Internal::IFuncCallQuery>& a_arg3) = 0;
			virtual void StackFramePushed(uint32_t, uint32_t, const Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) = 0;
			virtual void StackFramePopQueued(uint32_t, uint32_t, const Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) = 0;
			virtual void StackFramePopped(uint32_t, uint32_t, const Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) = 0;
		public:
		};
		static_assert(sizeof(IProfilePolicy) == 0x8);

	}
}