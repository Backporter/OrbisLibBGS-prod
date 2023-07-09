#pragma once

namespace ConsoleRE
{
	template <class T>
	struct GListNode
	{
	public:
		GListNode() : prev{ 0 }, next{ 0 } { }

		void Remove()
		{
			prev->next = next;
			next->prev = prev;
		}

		GListNode<T>* prev;
		GListNode<T>* next;
	};
}