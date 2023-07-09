#pragma once

#include "../../../OrbisUtil/include/std.h"
#include "../../../OrbisUtil/include/type_traits.h"

#include "../A/Array.h"
#include "../B/BSTSmartPointer.h"
#include "../T/TypeTraits.h"
#include "../V/Variable.h"

#include <vector>

namespace ConsoleRE
{
	namespace BSScript
	{
		template <typename T>
		struct is_form_pointer;

		template <class, class = void>
		class reference_array;

		template <class T>
		class reference_array<T, std::enable_if_t<std::disjunction_v<std::is_builtin_convertible<T>, is_form_pointer<T>>>>
		{
		public:
			using vector_type			 = std::vector<T>;
			using value_type			 = typename vector_type::value_type;
			using size_type				 = typename vector_type::size_type;
			using difference_type		 = typename vector_type::difference_type;
			using reference				 = typename vector_type::reference;
			using const_reference		 = typename vector_type::const_reference;
			using pointer				 = typename vector_type::pointer;
			using const_pointer			 = typename vector_type::const_pointer;
			using iterator				 = typename vector_type::iterator;
			using const_iterator		 = typename vector_type::const_iterator;
			using reverse_iterator		 = typename vector_type::reverse_iterator;
			using const_reverse_iterator = typename vector_type::const_reverse_iterator;
		public:
			reference_array& operator=(const Variable* a_args)
			{
				UnpackAll(a_args);
				return *this;
			}

			reference_array& operator=(reference_array&& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					PackAll();

					m_stl = std::move(a_rhs.m_stl);
					m_array = std::move(a_rhs.m_array);
				}

				return *this;
			}

			//
			operator vector_type() const							 { return m_stl; }
			reference			   operator[](size_type a_pos)		 { return m_stl[a_pos]; }
			const_reference		   operator[](size_type a_pos) const { return m_stl[a_pos]; }
			reference			   at(size_type a_pos)				 { return m_stl.at(a_pos); }
			const_reference		   at(size_type a_pos) const		 { return m_stl.at(a_pos); }
			reference			   front()							 { return m_stl.front(); }
			const_reference		   front() const					 { return m_stl.front(); }
			reference			   back()							 { return m_stl.back(); }
			const_reference		   back() const						 { return m_stl.back(); }
			pointer				   data() noexcept					 { return m_stl.data(); }
			const_pointer		   data() const noexcept			 { return m_stl.data(); }
			iterator			   begin() noexcept					 { return m_stl.begin(); }
			const_iterator		   begin() const noexcept			 { return m_stl.begin(); }
			const_iterator		   cbegin() const noexcept			 { return m_stl.cbegin(); }
			iterator			   end() noexcept					 { return m_stl.end(); }
			const_iterator		   end() const noexcept				 { return m_stl.end(); }
			const_iterator		   cend() const noexcept			 { return m_stl.cend(); }
			reverse_iterator       rbegin() noexcept				 { return m_stl.rbegin(); }
			const_reverse_iterator rbegin() const noexcept			 { return m_stl.rbegin(); }
			const_reverse_iterator crbegin() const noexcept			 { return m_stl.crbegin(); }
			reverse_iterator       rend() noexcept					 { return m_stl.rend(); }
			const_reverse_iterator rend() const noexcept			 { return m_stl.rend(); }
			const_reverse_iterator crend() const noexcept			 { return m_stl.crend(); }
			bool				   empty() const noexcept			 { return m_stl.empty(); }
			size_type			   size() const noexcept			 { return m_stl.size(); }
		public:
			reference_array(const reference_array&) = delete;

			reference_array() : m_stl(), m_array(nullptr)
			{}

			reference_array(Variable* const a_rhs) : m_stl(), m_array(nullptr)
			{
				UnpackAll(a_rhs);
			}
			
			reference_array(reference_array&& a_rhs) : m_stl(std::move(a_rhs.m_stl)), m_array(std::move(a_rhs.m_array))
			{}

			~reference_array()
			{
				PackAll();
			}

			void swap(reference_array& a_rhs)
			{
				std::swap(m_stl, a_rhs.m_stl);
				std::swap(m_array, a_rhs.m_array);
			}
		private:
			void PackAll()
			{
				if (m_array)
				{
					for (int i = 0; i < m_array->size(); i++)
					{
						(*m_array)[i].Pack(m_stl[i]);
					}
				}
			}

			void UnpackAll(Variable* const a_args)
			{
				assert(a_args && a_args->IsArray());
				auto arr = a_args->GetArray();
				if (m_array != arr)
				{
					m_array = std::move(arr);
					m_stl.reserve(m_array->size());
					for (auto& elem : *m_array)
					{
						m_stl.push_back(elem.template Unpack<value_type>());
					}
				}
			}
		protected:
			vector_type				m_stl;
			BSTSmartPointer<Array>	m_array;
		};

		template <typename T>
		void swap(reference_array<T>& a_lhs, reference_array<T>& a_rhs)
		{
			a_lhs.swap(a_rhs);
		}
	}

	template <typename T>
	using reference_array = BSScript::reference_array<T>;
}