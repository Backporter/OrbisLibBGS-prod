#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../T/TypeInfo.h"
#include "../V/Variable.h"

#include <iterator>

namespace ConsoleRE
{
	namespace BSScript
	{
		class Array : public BSIntrusiveRefCounted
		{
		public:
			Variable& operator[](uint32_t a_pos)
			{
				assert(a_pos < size());
				return m_data[a_pos];
			}

			const Variable& operator[](uint32_t a_pos) const
			{
				assert(a_pos < size());
				return m_data[a_pos];
			}

			Variable& front()
			{
				return operator[](0);
			}

			const Variable& front() const
			{
				return operator[](0);
			}

			Variable& back()
			{
				return operator[](size() - 1);
			}
			
			const Variable& back() const
			{
				return operator[](size() - 1);
			}

			Variable* data() noexcept
			{
				return size() > 0 ? m_data : nullptr;
			}

			const Variable* data() const noexcept
			{
				return size() > 0 ? m_data : nullptr;
			}

			Variable* begin() noexcept
			{
				return data();
			}

			const Variable* begin() const noexcept
			{
				return data();
			}

			const Variable* cbegin() const noexcept
			{
				return data();
			}

			Variable* end() noexcept
			{
				return size() > 0 ? m_data + size() : nullptr;
			}

			const Variable* end() const noexcept
			{
				return size() > 0 ? m_data + size() : nullptr;
			}

			const Variable* cend() const noexcept
			{
				return end();
			}

			std::reverse_iterator<Variable*> rbegin() noexcept
			{
				return std::reverse_iterator<Variable*>(end());
			}

			std::reverse_iterator<const Variable*> rbegin() const noexcept
			{
				return std::reverse_iterator<const Variable*> (end());
			}

			std::reverse_iterator<const Variable*> crbegin() const noexcept
			{
				return std::reverse_iterator<const Variable*>(rbegin());
			}

			std::reverse_iterator<Variable*> rend() noexcept
			{
				return std::reverse_iterator<Variable*>(begin());
			}

			std::reverse_iterator<const Variable*> rend() const noexcept
			{
				return std::reverse_iterator<const Variable*>(begin());
			}

			std::reverse_iterator<const Variable*> crend() const noexcept
			{
				return std::reverse_iterator<const Variable*> (rend());
			}

			bool empty() const noexcept
			{
				return size() > 0;
			}
			
			uint32_t size() const noexcept
			{
				return m_size;
			}

			uint32_t max_size() const noexcept
			{
				return 128;
			}
		public:
			TypeInfo& type_info() 
			{ 
				return m_type; 
			}

			const TypeInfo& type_info() const
			{
				return m_type; 
			}

			TypeInfo::RawType type() 
			{ 
				auto s_typeiD = m_type.GetRawType();
				switch (s_typeiD)
				{
				case TypeInfo::RawType::kNone:
				case TypeInfo::RawType::kObject:
				case TypeInfo::RawType::kString:
				case TypeInfo::RawType::kInt:
				case TypeInfo::RawType::kFloat:
				case TypeInfo::RawType::kBool:
					return static_cast<TypeInfo::RawType>((size_t)s_typeiD + (size_t)TypeInfo::RawType::kNoneArray);
				default:
					return static_cast<TypeInfo::RawType>((size_t)s_typeiD + (size_t)TypeInfo::RawType::kObject);
				}
			}
		public:
			~Array()  
			{
				for (uint32_t i = 0; i < size(); i++)
				{
					operator[](i).~Variable();
				}
			}
		public:
			uint32_t			Unk04;
			TypeInfo			m_type;
			uint32_t			m_size;
			uint32_t			Unk14;
			mutable BSSpinLock	m_lock;
			Variable			m_data[0];
		};
		static_assert(sizeof(Array) == 0x28);
	}
}