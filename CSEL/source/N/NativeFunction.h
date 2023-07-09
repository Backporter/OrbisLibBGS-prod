#pragma once

// 
#include "../../../OrbisUtil/include/type_traits.h"

#include "../B/BSTSmartPointer.h"
#include "../I/IObjectHandlePolicy.h"
#include "../N/NativeFunctionBase.h"
#include "../P/PackUnpack.h"
#include "../S/Stack.h"
#include "../S/StackFrame.h"
#include "../T/TypeTraits.h"
#include "../V/Variable.h"
#include "../V/VirtualMachine.h"

#include <utility>
#include <type_traits>

#ifndef NFDLSE
#define NFDLSE(A) decltype(A)
#endif

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Impl
		{
			template <class F, class Tuple, std::size_t... I, class... Args>
			constexpr decltype(auto) CallbackImpl(F a_func, Tuple&& a_tuple, std::index_sequence<I...>, Args&&... a_args)
			{
				return a_func(std::forward<Args>(a_args)..., std::get<I>(std::forward<Tuple>(a_tuple))...);
			}

			template <class F, class Tuple, class... Args>
			inline constexpr decltype(auto) CallBack(F a_func, Tuple&& a_tuple, Args&&... a_args)
			{
				return CallbackImpl(a_func, std::forward<Tuple>(a_tuple), std::index_sequence_for_tuple<Tuple>{}, std::forward<Args>(a_args)...);
			}


			template <class... Args, std::size_t... I>
			std::tuple<Args...> MakeTupleImpl(StackFrame& a_frame, uint32_t a_page, std::index_sequence<I...>)
			{
				return std::forward_as_tuple(a_frame.Get(I, a_page)->Unpack<Args>()...);
			}

			// tuple element construction order isn't guaranteed, so we need to wrap it
			template <class... Args>
			std::tuple<Args...> MakeTuple(StackFrame& a_frame, uint32_t a_page)
			{
				return MakeTupleImpl<Args...>(a_frame, a_page, std::index_sequence_for<Args...>{});
			}
		}
			
		template <bool IS_FULL_SIG, typename F, typename T_BASE, typename T_RET, class... Args>
		class NativeFunction : public NF_util::NativeFunctionBase
		{
		public:
			using base_type = T_BASE*;
			using result_type = T_RET;
			using func_t = typename std::remove_pointer<F>::type;
		public:
			NativeFunction() = delete;
			NativeFunction(const NativeFunction&) = delete;
			NativeFunction(NativeFunction&&) = delete;

			NativeFunction(const char* a_fnName, const char* a_className, F a_func) : NF_util::NativeFunctionBase(a_fnName, a_className, is_static_base_v<base_type>, sizeof...(Args)), func(a_func)
			{
				size_t i = 0;
				((m_params.m_entries[i++].second.SetType(GetRawType<Args>())), ...);
				m_returnType = GetRawType<result_type>();
			}

			~NativeFunction() override = default;

			bool HasFunc() override
			{ 
				return static_cast<bool>(func);
			}

			bool Run(Variable& a_base, Internal::VirtualMachine& a_vm, uint32_t a_stackID, Variable& a_result, StackFrame& a_frame) override
			{
#if NDEBUG
				if (xUtilty::INIHandler::g_Debug)
				{
#endif
					xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "%s::%s is being executed!", GetObjectTypeName().m_data, GetName().m_data);
#if NDEBUG
				}
#endif
				base_type base{};

				if constexpr (std::negation<is_static_base<base_type>>::value)
				{
					base = a_base.Unpack<base_type>();
					if (!base)
					{
						return false;
					}
				}

				auto pageoffset = a_frame.GetOffset();
				auto args = Impl::MakeTuple<Args...>(a_frame, pageoffset);

				if constexpr (std::is_void<result_type>::value)
				{
					if constexpr (IS_FULL_SIG)
					{
						Impl::CallBack(func, std::move(args), std::addressof(a_vm), a_stackID, std::move(base));
						a_result.SetNone();
					}
					else
					{
						Impl::CallBack(func, std::move(args), std::move(base));
						a_result.SetNone();
					}
				}
				else
				{
					if constexpr (IS_FULL_SIG)
					{
						auto result = Impl::CallBack(func, std::move(args), std::addressof(a_vm), a_stackID, std::move(base));
						a_result.Pack<T_RET>(std::move(result));
					}
					else
					{
						auto result = Impl::CallBack(func, std::move(args), std::move(base));
						a_result.Pack<T_RET>(std::move(result));
					}
				}
#if NDEBUG
				if (xUtilty::INIHandler::g_Debug)
				{
#endif
					xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "%s::%s has been executed!", GetObjectTypeName().m_data, GetName().m_data);
#if NDEBUG
				}
#endif
				return true;
			}
		protected:
			func_t* func;	// 0x58
		};
	}
}