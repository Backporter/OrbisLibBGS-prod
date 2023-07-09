#pragma once

namespace ConsoleRE
{
	template <class T>
	struct BSTSingletonExplicit
	{};

	template <class T>
	struct BSTSingletonImplicit
	{};

	template <class>
	struct BSTSingletonSDMBase;

	template <class T>
	struct BSTSingletonSDMOpStaticBuffer
	{};

	template <class T, class Alloc = BSTSingletonSDMOpStaticBuffer<T>>
	struct BSTSDMTraits
	{};

	template <class Traits>
	struct BSTSingletonSDMBase : public Traits, public Traits::Allocator
	{};

	template <class T, template <class> class Singleton = BSTSingletonSDMOpStaticBuffer>
	struct BSTSingletonSDM : public BSTSingletonSDMBase<BSTSDMTraits<T, Singleton<T>>>
	{};
}