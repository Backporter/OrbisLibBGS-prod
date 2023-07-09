#pragma once

#include "../../../OrbisUtil/include/Logger.h"

#include <utility>

namespace ConsoleRE
{
	template <typename T1, typename T2>
	class BSTTuple
	{
	public:
		BSTTuple(const BSTTuple&) = default;

		// 8)
		BSTTuple(BSTTuple&&) = default;

		~BSTTuple() = default;

		BSTTuple() : 
			first(), second()
		{}

		explicit BSTTuple(const T1& a_first, const T2& a_second) :
			first(a_first), second(a_second)
		{}

		template <typename U1, typename U2>
		explicit BSTTuple(U1&& a_first, U2&& a_second) :
			first(std::forward<U1>(a_first)), second(std::forward<U2>(a_second))
		{}

		template <class U1, class U2>
		explicit BSTTuple(const BSTTuple<U1, U2>& a_rhs) :
			first(a_rhs.first), second(a_rhs.second)
		{}

		template <class U1, class U2>
		explicit BSTTuple(BSTTuple<U1, U2>&& a_rhs) :
			first(std::forward<U1>(a_rhs.first)), second(std::forward<U2>(a_rhs.second))
		{}
	public:
		void DumpEntriescSTR(xUtilty::Log* instance)
		{
			instance->Write(xUtilty::Log::logLevel::kNone, "\t\tkey: %S ", first);
			instance->Write(xUtilty::Log::logLevel::kNone, "\t\ttranslation: %S", second);
		}
	public:
		T1 first;
		T2 second;
	};
	static_assert(sizeof(BSTTuple<void*, void*>) == 0x10);
}