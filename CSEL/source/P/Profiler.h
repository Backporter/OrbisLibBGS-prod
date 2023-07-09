#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSTHashMap.h"
#include "../I/IProfilePolicy.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class Profiler : public BSScript::IProfilePolicy
		{
		public:
			~Profiler() override;

			// override (BSScript::IProfilePolicy)
			void StackFramePushQueued(uint32_t a_arg1, uint32_t a_arg2, const BSTSmartPointer<BSScript::Internal::IFuncCallQuery>& a_arg3) override;
			void StackFramePushed(uint32_t a_arg1, uint32_t a_arg2, const BSScript::Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) override;
			void StackFramePopQueued(uint32_t a_arg1, uint32_t a_arg2, const BSScript::Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) override;
			void StackFramePopped(uint32_t a_arg1, uint32_t a_arg2, const BSScript::Variable& a_arg3, const BSFixedString& a_arg4, const BSFixedString& a_arg5, const BSFixedString& a_arg6) override;
		public:
			mutable BSSpinLock           unk08;
			BSTHashMap<UnkKey, UnkValue> unk10;
			BSTHashMap<UnkKey, UnkValue> unk40;
			BSTHashMap<UnkKey, UnkValue> unk70;
			uint64_t					 unkA0;
			uint64_t					 unkA8;
			uint64_t					 unkB0;
			uint64_t					 unkB8;
			uint64_t					 unkC0;
			uint64_t					 unkC8;
			uint64_t					 unkD0;
			uint64_t					 unkD8;
		};
		static_assert(sizeof(Profiler) == 0xB8, "#");
	}
}