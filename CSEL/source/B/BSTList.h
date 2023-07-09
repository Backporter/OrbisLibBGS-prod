#pragma once

#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <utility>
#include <assert.h>

namespace ConsoleRE
{
	template <class T>
	class BSSimpleList
	{
	public:
		struct Node
		{
		public:
			Node& operator=(Node&& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					m_item = std::move(a_rhs.m_item);
					m_next = std::move(a_rhs.m_next);
				}

				return *this;
			}

			Node& operator=(const Node& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					m_item = a_rhs.m_item;
					m_next = a_rhs.m_next;
				}

				return *this;
			}
		public:
			Node() : m_item{}, m_next(nullptr) 
			{
			}

			Node(T a_type, Node* a_next) : m_item(a_type), m_next(a_next) 
			{
			}

			Node(const T& a_type) : m_item(a_type), m_next(nullptr)
			{ 
			}
			
			~Node() 
			{
			}
			
		public:
			T&		item() { return m_item; }
			Node*	next() { return m_next; }
		public:
			T		m_item;
			Node*	m_next;
		};

		struct NodePoint
		{
		public:
			NodePoint() : m_node(NULL), m_index(NULL) {}
			NodePoint(Node* a_node, uint64_t a_index) : m_node(a_node), m_index(a_index) { }
			~NodePoint() { }

			bool Initialize(Node* a_node, uint64_t a_index) { m_node = a_node; m_index = a_index; return true; }
		public:
			Node*		m_node;
			uint64_t    m_index;
		};
		
		template <class Y>
		class Iterator_base
		{
		public:
			constexpr Iterator_base& operator=(const Iterator_base& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs))
				{
					_Alval = a_rhs._Alval;
				}

				return *this;
			}

			constexpr Iterator_base& operator=(Iterator_base&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs))
				{
					_Alval = std::move(a_rhs._Alval);
					a_rhs._Alval = nullptr;
				}

				return *this;
			}

			constexpr Iterator_base& operator++() noexcept
			{
				assert(_Alval);
				_Alval = _Alval->m_next;
				return *this;
			}

			constexpr Y* operator->() const noexcept
			{
				return std::addressof(_Alval->m_item);
			}

			constexpr Y& operator*() const noexcept
			{
				return _Alval->m_item;

			}

			constexpr bool operator==(const Iterator_base& a_rhs) const noexcept
			{
				return _Alval == a_rhs._Alval;
			}
			
			constexpr bool operator!=(const Iterator_base& a_rhs) const noexcept
			{
				return _Alval != a_rhs._Alval;
			}

			constexpr operator bool()
			{
				return static_cast<bool>(_Alval);
			}
		public:
			Iterator_base() noexcept : _Alval(nullptr)
			{
			}

			Iterator_base(const Iterator_base& a_rhs) noexcept : _Alval(a_rhs._Alval)
			{
			}
			
			Iterator_base(Iterator_base&& a_rhs) noexcept : _Alval(std::move(a_rhs._Alval))
			{
				a_rhs._Alval = nullptr;
			}

			Iterator_base(Node* a_node) : _Alval(a_node)
			{
			}

			~Iterator_base()
			{
				_Alval = nullptr;
			}
		public:
			constexpr Node* get() noexcept { return _Alval; }
			constexpr const Node* get() const noexcept { return _Alval; }
		public:
			Node* _Alval;
		};
	public:
		using Iterator = Iterator_base<T>;
		using const_Iterator = Iterator_base<const T>;

		inline T& front() { assert(!empty()); return *begin(); }
		inline const T& front() const { assert(!empty()); return *begin();  }

		inline Iterator       begin() { return empty() ? end() : Iterator(Head()); }
		inline const_Iterator begin() const { return empty() ? end() : Iterator(Head()); }
		inline const_Iterator cbegin() const { return begin(); }

		constexpr Iterator       end() noexcept { return Iterator(nullptr); }
		constexpr const_Iterator end() const noexcept { return const_Iterator(nullptr); }
		constexpr const_Iterator cend() const noexcept { return end(); }

		inline bool empty() const { return !list.m_next && !list.m_item; }
	public:			
		template <class Op>
		void		Visit(Op& op, Node* prev = NULL)
		{
			Node* pCur = (prev) ? prev->m_next : Head();
			bool bContinue = true;
			while (pCur && bContinue)
			{
				bContinue = op.Accept(pCur->m_item);
				if (bContinue)
				{
					pCur = pCur->m_next;
				}
			}
		}

		template <class Op>
		uint32_t CountIf(Op& a_op)
		{
			uint32_t count = 0;
			Node* pCur = Head();
			while (pCur)
			{
				if (pCur->m_item && a_op.Accept(pCur->m_item))
					count++;

				pCur = pCur->m_next;
			}

			return count;
		}
	public:
		Node*		Head() { return static_cast<Node*>(&list); }

		Node*		Tail() 
		{ 
			Node* m_node = Head(); 
			if (m_node)
			{
				while (m_node->m_next)
					m_node = m_node->m_next;
			}

			return m_node;
		}

		void		GetNode(int32_t val, NodePoint& a_out)
		{
			int32_t n = 0;
			Node* m_node = Head();
			while (m_node && m_node->item())
			{
				if (n == val) 
					break;

				if (val == -2 && !m_node->next())
					break;

				m_node = m_node->next();
				n++;
			}

			a_out.m_node = m_node;
			a_out.m_index = n;
			return;
		}

		uint32_t	Count()            
		{ 
			NodePoint m_point;
			GetNode(-3, m_point);
			
			if (m_point.m_index > 0)
				return m_point.m_index;
			else
				return 0;
		}

		T			GetItem(int32_t val)
		{
			NodePoint m_point;
			GetNode(val, m_point);
			
			if (m_point.m_index == val)
				return m_point.m_node->item();
			else
				return nullptr;
		}
	public:
		Node list;
	};
}