#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class ObjectTypeInfo;

		class TypeInfo
		{
		public:
			enum class RawType : size_t
			{
				// types
				kNone = 0,
				kObject = 1,
				kString = 2,
				kInt = 3,
				kFloat = 4,
				kBool = 5,

				// array types
				kNoneArray = 10,
				kObjectArray = 11,
				kStringArray = 12,
				kIntArray = 13,
				kFloatArray = 14,
				kBoolArray = 15,

				// ???
				kArraysEnd = 16,
			};

			TypeInfo& operator=(const TypeInfo& a_rhs)
			{
				m_type = a_rhs.m_type;
				return *this;
			}

			TypeInfo& operator=(TypeInfo&& a_rhs)
			{
				m_type = std::move(a_rhs.m_type);
				a_rhs.m_type = RawType::kNone;
				return *this;
			}

			TypeInfo& operator=(RawType a_rhs)
			{
				m_type = a_rhs;
				return *this;
			}
		public:
			TypeInfo() : m_type(RawType::kNone) 
			{
			}

			TypeInfo(RawType src) : m_type(src) 
			{ 
			}

			TypeInfo(const TypeInfo& a_rhs) : m_type(a_rhs.m_type)
			{
			}

			TypeInfo(TypeInfo&& a_rhs) : m_type(std::move(a_rhs.m_type))
			{
				a_rhs.m_type = RawType::kNone;
			}

			~TypeInfo() 
			{
			}

			RawType				GetRawType()			
			{ 
				return m_type; 
			}
			
			ObjectTypeInfo*		GetTypeInfo()			
			{ 
				size_t rawtype = static_cast<size_t>(GetRawType());
				rawtype &= ~(size_t)RawType::kObject;
				return reinterpret_cast<ObjectTypeInfo*>(rawtype);					
			}
			
			RawType	GetUnmangledRawType()
			{
				if (m_type < RawType::kArraysEnd)
				{
					return GetRawType();
				}
				else
				{
					return (RawType)((size_t)m_type & (size_t)RawType::kObject) == RawType::kObject ? RawType::kObjectArray : RawType::kObject;
				}
			}

			bool			IsBool(void)			{ return (m_type == TypeInfo::RawType::kBool); }
			bool			IsFloat(void)			{ return (m_type == TypeInfo::RawType::kFloat); }
			bool			IsInt(void)				{ return (m_type == TypeInfo::RawType::kInt); }
			bool			IsString(void)			{ return (m_type == TypeInfo::RawType::kString); }
			bool			IsNoneArray(void)		{ return (m_type == TypeInfo::RawType::kNoneArray); }
			bool			IsNoneObject(void)		{ return (m_type == TypeInfo::RawType::kNone); }
			bool			IsLiteralArray(void)	{ return ((size_t)m_type - 12) <= 3; }
			bool			IsObjectArray(void)		{ return (m_type >= RawType::kArraysEnd) && (RawType)((size_t)m_type & (size_t)RawType::kObject) == RawType::kObject; }
			bool			IsArray(void)			{ return IsLiteralArray() || IsObjectArray(); }
			bool			IsObject(void)			{ return GetUnmangledRawType() == TypeInfo::RawType::kObject; }
			void			SetType(RawType a_type) { m_type = a_type;  }
		public:
			RawType m_type;
		};
	}
}