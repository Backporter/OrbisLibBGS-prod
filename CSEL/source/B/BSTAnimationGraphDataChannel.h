#pragma once

#include "../B/BSAnimationGraphChannel.h"

namespace ConsoleRE
{
	template <class T, class V, template <class T2, class V2> class C>
	class BSTAnimationGraphDataChannel : public BSAnimationGraphChannel, public C<T, V>
	{
	public:
	};
}